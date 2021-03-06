#include "mlb_button.h"

MlbButton *mlb_btn_init(MlbButton *btn, uint8_t i_pin, uint16_t flags, ...)
{
  assert(btn != NULL);
  *btn = (MlbButton) { i_pin, flags };

  if (mlb_btn_is_single(btn))
    return btn; 

  va_list va;
  va_start(va, flags);

  btn->first_delay = mlb_millis_to_uis(va_arg(va, unsigned long));

  if (mlb_btn_is_typematic(btn))
    btn->second_delay = mlb_millis_to_uis(va_arg(va, unsigned long));

  va_end(va);

  return mlb_btn_post(btn);
}

static inline uint8_t depressed_state(const MlbButton *btn)
{
  return MLB_IS_BIT_SET(btn->flags, MLB_BTN_PULL_UP) ? HIGH : LOW;
}

static inline uint8_t released_state(const MlbButton *btn)
{
  return MLB_IS_BIT_SET(btn->flags, MLB_BTN_PULL_UP) ? LOW : HIGH;
}

static inline void register_push(MlbButton *btn)
{
  assert(btn != NULL);
  if (MLB_IS_BIT_SET(btn->flags, MLB_BTN_BUFFERED_FULL))
    ++btn->n_pushes;
  else
    btn->n_pushes = 1;
}

static inline void register_long_push(MlbButton *btn)
{
  assert(mlb_btn_is_long(btn));
  btn->n_pushes = 0;
  btn->flags = MLB_SET_BITS(btn->flags, MLB_BTN_LONG_BUFFERED__);
}

CO_FUNCTION_DEFINITION(mlb_single_button_execute)
{
  CO_BEGIN

  for (;;)
  {
    if (!MLB_CO_SUSPENDABLE_IS_RUNNING(*COP.btn))
    {
      CO_YIELD();
      continue;
    }

    /* Wait for a push */
    co_wait_for_stable_pin_inline(COP.btn->i_pin, depressed_state(COP.btn)); 
    COP.btn->flags = MLB_SET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);

    if (!MLB_IS_BIT_SET(COP.btn->flags, MLB_BTN_ON_RELEASE))
      register_push(COP.btn);

    /* Wait for release */
    co_wait_for_stable_pin_inline(COP.btn->i_pin, released_state(COP.btn)); 
    COP.btn->flags = MLB_RESET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);

    if (MLB_IS_BIT_SET(COP.btn->flags, MLB_BTN_ON_RELEASE))
      register_push(COP.btn);
  }

  CO_END
}

CO_FUNCTION_DEFINITION(mlb_long_button_execute)
{
  CO_BEGIN

  for (;;)
  {
    if (!MLB_CO_SUSPENDABLE_IS_RUNNING(*COP.btn))
    {
      CO_YIELD();
      continue;
    }

    /* Wait for a push */
    co_wait_for_stable_pin_inline(COP.btn->i_pin, depressed_state(COP.btn)); 
    COP.btn->flags = MLB_SET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);

    /* Wait for release within 'first_delay' */
    uint8_t final_state;
    co_wait_for_stable_pin_lim_inline(COP.btn->i_pin, released_state(COP.btn),
      mlb_uis_to_millis(COP.btn->first_delay), final_state);

    if (final_state == MLB_UNDEFINED)
    { /* Let's not even try to register anything for 'MLB_UNDEFINED' */
      co_wait_for_stable_pin_inline(COP.btn->i_pin, released_state(COP.btn)); 
      COP.btn->flags = MLB_RESET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);
      continue;
    }

    if (final_state == released_state(COP.btn))
    { /* Released within 'first_delay' */
      COP.btn->flags = MLB_RESET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);
      register_push(COP.btn);
    }
    else
    { /* Still being held ... */
      if (!MLB_IS_BIT_SET(COP.btn->flags, MLB_BTN_ON_RELEASE))
        register_long_push(COP.btn);

      /* Wait for the actual release */
      co_wait_for_stable_pin_inline(COP.btn->i_pin, released_state(COP.btn)); 
      COP.btn->flags = MLB_RESET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);

      if (MLB_IS_BIT_SET(COP.btn->flags, MLB_BTN_ON_RELEASE))
        register_long_push(COP.btn);
    }
  }

  CO_END
}

CO_FUNCTION_DEFINITION(mlb_typematic_button_execute)
{
  CO_BEGIN

  for (;;)
  {
    if (!MLB_CO_SUSPENDABLE_IS_RUNNING(*COP.btn))
    {
      CO_YIELD();
      continue;
    }

    /* Wait for a push */
    co_wait_for_stable_pin_inline(COP.btn->i_pin, depressed_state(COP.btn)); 
    COP.btn->flags = MLB_SET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);

    register_push(COP.btn);

    /* Wait for release within 'first_delay' */
    uint8_t final_state;
    co_wait_for_stable_pin_lim_inline(COP.btn->i_pin, released_state(COP.btn),
      mlb_uis_to_millis(COP.btn->first_delay), final_state);

    if (final_state == released_state(COP.btn))
    {
      COP.btn->flags = MLB_RESET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);
      continue;
    }

    if (final_state != MLB_UNDEFINED)
      register_push(COP.btn);

    do
    {
      co_wait_for_stable_pin_lim_inline(COP.btn->i_pin, released_state(COP.btn),
        mlb_uis_to_millis(COP.btn->second_delay), final_state);

      if (final_state == released_state(COP.btn))
      {
        COP.btn->flags = MLB_RESET_BITS(COP.btn->flags, MLB_BTN_IS_DEPRESSED);
        break;
      }

      if (final_state != MLB_UNDEFINED)
        register_push(COP.btn);

    } while (true);
  }

  CO_END
}

/****************************************************************************************/

CO_FUNCTION_DEFINITION(mlb_buttons_execute)
{
  CO_BEGIN_DYNAMIC

  COL.sub_stacks = CO_ZALLOCA(COP.mlb_btns->n * sizeof *COL.sub_stacks, MLB_STRICT_ALIGN_MAX);

  for (;;)
  {
    if (!MLB_CO_SUSPENDABLE_IS_RUNNING(*COP.mlb_btns))
    {
      CO_YIELD();
      continue;
    }

    for (COL.i = 0; COL.i < COP.mlb_btns->n; ++COL.i)
    {
      MlbButton *btn = mlb_btns_at(COP.mlb_btns, COL.i);
      if (mlb_btn_is_single(btn))
        CO_SUB_ROOT_INVOKE_SSIZE(10001, COL.sub_stacks[COL.i], sizeof COL.sub_stacks[COL.i],
          mlb_single_button_execute, btn);
      else if (mlb_btn_is_long(btn))
        CO_SUB_ROOT_INVOKE_SSIZE(10002, COL.sub_stacks[COL.i], sizeof COL.sub_stacks[COL.i],
          mlb_long_button_execute, btn);
      else
        CO_SUB_ROOT_INVOKE_SSIZE(10003, COL.sub_stacks[COL.i], sizeof COL.sub_stacks[COL.i], 
          mlb_typematic_button_execute, btn);
    }

    CO_YIELD();
  }

  CO_END
}
