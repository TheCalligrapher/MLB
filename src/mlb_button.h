#ifndef MLB_BUTTON_H_
#define MLB_BUTTON_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"
#include "mlb_arduino_co.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

/* #define MLB_CO_IS_SUSPENDED  0x01 */

/* Setup flags */

#define MLB_BTN_PULL_DOWN       0x0000
#define MLB_BTN_PULL_UP         0x0002
/* What pin state to look for to detect a depressed button */

#define MLB_BTN_BUILT_IN_PULL   0x0004
/* The button relies on the board's built-in pull resistor */

#define MLB_BTN_SINGLE          0x0000
/* Regular button. 
   Only one regular 'PT_PUSH' is registered (on delay or on release) after a fixed 
   debouncing delay. 'PT_PUSH'es can be buffered, if requested */

#define MLB_BTN_LONG            0x0008 
/* Button with long press option.
   Registers a 'PT_PUSH' if pushed and released before a specified long delay. 'PT_PUSH'es 
   can be buffered, if requested. If instead held in depressed state for user-specified 
   long delay, registers 'PT_LONG' (on delay or on release), which purges all previous 
   pushes, if any are buffered */

#define MLB_BTN_TYPEMATIC       0x0010 
/* Typematic button.
   Two delays are assiciated with such button: first and second. All pushes are on delay. 
   It registers an initial 'PT_PUSH', then waits for the first delay and (if still 
   depressed) registers a second 'PT_PUSH' and then generates a sequence of 'PT_PUSH'es 
   after each consequitive second delay. All 'PT_PUSH'es can be buffered, if requested */

#define MLB_BTN_ON_DELAY        0x0000 
/* Push is registered when a specific delay passes (a debouncing delay or a user-specified delay) */
#define MLB_BTN_ON_RELEASE      0x0020
/* Push is registered after a specific delay passes (a debouncing delay or a long delay) 
   and the button is subsequently released */

#define MLB_BTN_BUFFERED_1      0x0000
/* No more that 1 push is buffered */
#define MLB_BTN_BUFFERED_FULL   0x0040
/* All pushes are buffered and extracted one by one */

/* Status flags */

#define MLB_BTN_LONG_BUFFERED__ 0x0080
/* Used with long buttons. Means: long push is buffered */

#define MLB_BTN_IS_DEPRESSED    0x0100

/****************************************************************************************/

typedef enum MlbBtnPushType
{
  MLB_PT_NONE = 0,
  MLB_PT_PUSH = 1,
  MLB_PT_LONG = 2

} MlbBtnPushType;

typedef struct MlbButton
{
  uint8_t i_pin;
  uint16_t flags;
  MlbUis first_delay, second_delay;
  unsigned n_pushes;
} MlbButton;

#define MLB_BTN_INIT_SINGLE_PD(pin)\
  { pin, MLB_BTN_SINGLE | MLB_BTN_PULL_DOWN | MLB_BTN_BUILT_IN_PULL } 
#define MLB_BTN_INIT_SINGLE_PU(pin)\
  { pin, MLB_BTN_SINGLE | MLB_BTN_PULL_UP } 

#define MLB_BTN_INIT_LONG_PD(pin, delay)\
  { pin, MLB_BTN_LONG | MLB_BTN_PULL_DOWN | MLB_BTN_BUILT_IN_PULL,\
    (delay) / MLB_UIS_MUL } 
#define MLB_BTN_INIT_LONG_PU(pin, delay)\
  { pin, MLB_BTN_LONG | MLB_BTN_PULL_UP, (delay) / MLB_UIS_MUL } 

#define MLB_BTN_INIT_TPM_PD(pin, first, second)\
  { pin, MLB_BTN_TYPEMATIC | MLB_BTN_PULL_DOWN | MLB_BTN_BUILT_IN_PULL | MLB_BTN_BUFFERED_FULL,\
    (first) / MLB_UIS_MUL, (second) / MLB_UIS_MUL } 
#define MLB_BTN_INIT_TPM_PU(pin, first, second)\
  { pin, MLB_BTN_TYPEMATIC | MLB_BTN_BUFFERED_FULL | MLB_BTN_PULL_UP,\
    (first) / MLB_UIS_MUL, (second) / MLB_UIS_MUL } 

/****************************************************************************************/

static inline bool mlb_btn_is_single(const MlbButton *btn)
{
  assert(btn != NULL);
  return (btn->flags & (MLB_BTN_LONG | MLB_BTN_TYPEMATIC)) == 0;
}

static inline bool mlb_btn_is_long(const MlbButton *btn)
{
  assert(btn != NULL);
  return (btn->flags & (MLB_BTN_LONG | MLB_BTN_TYPEMATIC)) == MLB_BTN_LONG;
}

static inline bool mlb_btn_is_typematic(const MlbButton *btn)
{
  assert(btn != NULL);
  return (btn->flags & (MLB_BTN_LONG | MLB_BTN_TYPEMATIC)) == MLB_BTN_TYPEMATIC;
}

static inline MlbButton *mlb_btn_post(MlbButton *btn)
{ /* Post-init routine (finalizer) to be applied to 'STATIC_INIT' initialized buttons */
  assert(btn != NULL);
  pinMode(btn->i_pin, 
    MLB_IS_BIT_SET(btn->flags, MLB_BTN_BUILT_IN_PULL) && 
      !MLB_IS_BIT_SET(btn->flags, MLB_BTN_PULL_UP) ? INPUT_PULLUP : INPUT);
  return btn;
}

MlbButton *mlb_btn_init(MlbButton *btn, uint8_t i_pin, uint16_t flags, ...);

static inline int mlb_btn_attach_pin(MlbButton *btn, uint8_t i_pin)
{ 
  assert(btn != NULL);
  MLB_SWAP(uint8_t, btn->i_pin, i_pin);
  pinMode(btn->i_pin, 
    MLB_IS_BIT_SET(btn->flags, MLB_BTN_BUILT_IN_PULL) && 
      !MLB_IS_BIT_SET(btn->flags, MLB_BTN_PULL_UP) ? INPUT_PULLUP : INPUT);
  return i_pin;
}

static inline MlbButton *mlb_btn_init_simple(MlbButton *btn, 
                                             uint8_t i_pin, uint16_t flags)
{
  return mlb_btn_init(btn, i_pin, MLB_BTN_SINGLE | flags);
}

static inline MlbButton *mlb_btn_init_long(MlbButton *btn, 
                                           uint8_t i_pin, uint16_t flags,
                                           unsigned long long_delay)
{
  return mlb_btn_init(btn, i_pin, MLB_BTN_LONG | flags, long_delay);
}

static inline MlbButton *mlb_btn_init_typematic(MlbButton *btn, 
                                                uint8_t i_pin, uint16_t flags,
                                                unsigned long first_delay,
                                                unsigned long typematic_delay)
{
  return mlb_btn_init(btn, i_pin, MLB_BTN_TYPEMATIC | flags, first_delay, typematic_delay);
}

/****************************************************************************************/

static inline MlbBtnPushType mlb_btn_consume_push(MlbButton *btn)
{
  assert(btn != NULL);

  if (MLB_CONSUME_FLAG(btn->flags, MLB_BTN_LONG_BUFFERED__))
  {
    assert(mlb_btn_is_long(btn));
    return MLB_PT_LONG;
  }

  if (btn->n_pushes > 0)
  {
    --btn->n_pushes;
    return MLB_PT_PUSH;
  }
  
  return MLB_PT_NONE;
}

static inline bool mlb_btn_is_depressed(const MlbButton *btn)
{
  assert(btn != NULL);
  return MLB_IS_BIT_SET(btn->flags, MLB_BTN_IS_DEPRESSED);
}

static inline bool mlb_btn_purge(MlbButton *btn)
{
  btn->n_pushes = 0;
  btn->flags = MLB_RESET_BITS(btn->flags, MLB_BTN_LONG_BUFFERED__);
}

/****************************************************************************************/

CO_PROTOTYPE_NO_LOCALS(mlb_single_button_execute, MlbButton *btn);
CO_PROTOTYPE_NO_LOCALS(mlb_long_button_execute, MlbButton *btn);
CO_PROTOTYPE_NO_LOCALS(mlb_typematic_button_execute, MlbButton *btn);

/****************************************************************************************/

/* #define MLB_CO_IS_SUSPENDED 0x1 */

typedef struct MlbButtons
{
  MlbButton *buttons;
  unsigned n;
  uint8_t flags;
} MlbButtons;

#define MLB_BTNSA_NAME(name_) MLB_PP_CONCAT(name_, _btna)

mlb_static_assert((MLB_BTN_SINGLE | MLB_BTN_PULL_DOWN) == 0);
#define MLB_BTNS_SINGLE_PD_N(n_)\
  static MlbButton MLB_BTNSA_NAME(name_)[n_] = { 0 };\
  linkage_ MlbButtons name_ = { MLB_BTNSA_NAME(name_), n_ };

#define MLB_BTNS(linkage_, name_, ...)\
  static MlbButton MLB_BTNSA_NAME(name_)[] = { __VA_ARGS__ };\
  linkage_ MlbButtons name_ = { MLB_BTNSA_NAME(name_), MLB_ARRAY_N(MLB_BTNSA_NAME(name_)) };

/****************************************************************************************/

static inline MlbButton *mlb_btns_at(const MlbButtons *mlb_btns, unsigned i)
{
  assert(mlb_btns != NULL && i < mlb_btns->n);
  return &mlb_btns->buttons[i];
}

static inline MlbButtons *mlb_btns_post(MlbButtons *mlb_btns)
{ /* Post-init routine (finalizer) to be applied to 'STATIC_INIT' initialized buttons */
  assert(mlb_btns != NULL);
  for (unsigned i = 0; i < mlb_btns->n; ++i)
    mlb_btn_post(mlb_btns_at(mlb_btns, i));
  return mlb_btns;
}

/****************************************************************************************/

#define MLB_BTN_MAX_SUSG COF_FULL_SUSG(mlb_typematic_button_execute)
mlb_static_assert(MLB_BTN_MAX_SUSG == 
  MLB_MAX(COF_FULL_SUSG(mlb_single_button_execute), 
  MLB_MAX(COF_FULL_SUSG(mlb_long_button_execute), 
          COF_FULL_SUSG(mlb_typematic_button_execute))));

#define MLB_BTN_ALIGNED_SUSG MLB_STRICT_ALIGN_UP(MLB_BTN_MAX_SUSG, CO_STACK_ALIGN)

CO_PROTOTYPE_DYNAMIC(mlb_buttons_execute, MlbButtons *mlb_btns)
{
  unsigned char (*sub_stacks)[MLB_BTN_ALIGNED_SUSG];
  unsigned i;
}
CO_PROTOTYPE_END

#define MLB_BTNS_ASPS(n_)\
  COF_ASP(mlb_buttons_execute), (MLB_STRICT_ALIGN_MAX, (n_) * MLB_BTN_ALIGNED_SUSG)

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_BUTTON_H_ */
