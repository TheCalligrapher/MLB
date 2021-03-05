#ifndef MLB_ARDUINO_CO_H_
#define MLB_ARDUINO_CO_H_

#include "mlb_util.h"

#include "co/mlb_co.h"

C_LINKAGE_BEGIN

/****************************************************************************************/
/* Support for root wait */

typedef struct CoRootContext
{
  unsigned long duration, start, local_start;
} CoRootContext;

static inline void co_init_root_context(CoRootContext *corc)
{
  *corc = (CoRootContext) { 0 };
}

static inline bool co_process_root_context(CoRootContext *corc)
{ 
  if (corc->duration == 0)
    return true;

  if (corc->duration == MLB_MLS_INF)
    return false;

  if (mlb_millis() - corc->start < corc->duration)
    return false;

  corc->duration = 0;
  return true;
}

/****************************************************************************************/

#define MLB_STATE_DEBOUNCING_DELAY 50ul

/****************************************************************************************/
/* Guarantees at least one 'CO_YIELD()', even if the requested duration is zero */

#define co_delay_inline(ul_duration) do {\
    CORC.start = mlb_millis();\
    CORC.duration = ul_duration;\
    CO_YIELD__(1);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_delay, unsigned long duration);

/****************************************************************************************/

#define co_wait_for_pin_inline(ui8_pin /* p */, ui8_target_state /* p */) do {\
    while (digitalRead(ui8_pin) != (ui8_target_state))\
      CO_YIELD__(1);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_wait_for_pin, uint8_t i_pin, uint8_t target_state);

/****************************************************************************************/

#define co_wait_for_stable_pin_inline(ui8_pin /* p */, ui8_target_state /* p */) do {\
    bool retry;\
    do\
    {\
      while (digitalRead(ui8_pin) != (ui8_target_state))\
        CO_YIELD__(1);\
      \
      retry = false;\
      for (CORC.start = mlb_millis(); mlb_millis() - CORC.start < MLB_STATE_DEBOUNCING_DELAY; )\
      {\
        if ((retry = digitalRead(ui8_pin) != (ui8_target_state)))\
          break;\
        CO_YIELD__(2);\
        retry = false;\
      }\
    } while (retry);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_wait_for_stable_pin, uint8_t i_pin, uint8_t target_state);

/****************************************************************************************/

#define co_wait_for_pin_lim_inline(ui8_pin /* p */, ui8_target_state /* p */,\
                                   ul_duration /* p */ , ui8_final_state /* w */) do {\
    (ui8_final_state) = digitalRead(ui8_pin);\
    if ((ul_duration) == 0)\
      break;\
    \
    for (CORC.start = mlb_millis(); mlb_millis() - CORC.start < (ul_duration); )\
    {\
      if ((ui8_final_state) == (ui8_target_state))\
        break;\
      \
      CO_YIELD__(1);\
      (ui8_final_state) = digitalRead(ui8_pin);\
    }\
  } while (0)

/* Note that 'co_wait_for_pin_lim_inline' does not require 'ui8_final_state' to be 
   persistent */

CO_PROTOTYPE_NO_LOCALS(co_wait_for_pin_lim, 
                       uint8_t i_pin, uint8_t target_state, unsigned long duration, 
                       uint8_t *mlb_restrict final_state);

/****************************************************************************************/

#define co_wait_for_stable_pin_lim_inline(ui8_pin /* p */, ui8_target_state /* p */,\
                                          ul_duration /* p */ , ui8_final_state /* pw */) do {\
    (ui8_final_state) = MLB_UNDEFINED;\
    if ((ul_duration) == 0)\
      break;\
    \
    CORC.start = mlb_millis();\
    bool done = false;\
    do\
    {\
      CORC.local_start = mlb_millis();\
      uint8_t state;\
      while ((state = digitalRead(ui8_pin)) != (ui8_target_state))\
      {\
        if (mlb_millis() - CORC.local_start >= MLB_STATE_DEBOUNCING_DELAY)\
          (ui8_final_state) = state;\
        \
        if ((done = mlb_millis() - CORC.start > (ul_duration)))\
          break;\
        \
        CO_YIELD__(1);\
        done = false;\
      }\
      \
      if (done)\
        break;\
      \
      CORC.local_start = mlb_millis();\
      while ((state = digitalRead(ui8_pin)) == (ui8_target_state))\
      {\
        if (mlb_millis() - CORC.local_start >= MLB_STATE_DEBOUNCING_DELAY)\
        {\
          (ui8_final_state) = state;\
          done = true;\
          break;\
        }\
        \
        if ((done = mlb_millis() - CORC.start > (ul_duration)))\
          break;\
        \
        CO_YIELD__(2);\
        done = false;\
      }\
    } while (!done);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_wait_for_stable_pin_lim, 
                       uint8_t i_pin, uint8_t target_state, unsigned long duration, 
                       uint8_t *mlb_restrict final_state);

/****************************************************************************************/

#if CO_TRACK_STACK_USAGE || CO_REPORT_STACK_SIZE
  extern void *g_mlb_susg_printer;
  void mlb_co_susg_default_reporter(unsigned id, size_t usage);
  void mlb_co_ssize_default_reporter(unsigned id, size_t size);
#endif

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_ARDUINO_CO_H_ */
