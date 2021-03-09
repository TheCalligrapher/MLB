#ifndef MLB_ARDUINO_CO_H_
#define MLB_ARDUINO_CO_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"

#define CO_ENABLE_ROOT_CONTEXT 1
#include "co/mlb_co.h"

#include <Arduino.h>
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/
/* Support for root wait */

typedef struct CoRootContext
{
  unsigned long mls_duration, mls_start, mls_local_start;
} CoRootContext;

static inline void co_init_root_context(CoRootContext *corc)
{
  *corc = MLB_INITIALIZER(CoRootContext, { 0 });
}

static inline bool co_process_root_context(CoRootContext *corc)
{ 
  if (corc->mls_duration == 0)
    return true;

  if (corc->mls_duration == MLB_MLS_INF)
    return false;

  if (mlb_millis() - corc->mls_start < corc->mls_duration)
    return false;

  corc->mls_duration = 0;
  return true;
}

/****************************************************************************************/

#define MLB_STATE_DEBOUNCING_DELAY 50ul

/****************************************************************************************/
/* Guarantees at least one 'CO_YIELD()', even if the requested duration is zero */

#define co_delay_inline(mls_duration_) do {\
    CORC.mls_start = mlb_millis();\
    CORC.mls_duration = (mls_duration_);\
    CO_YIELD__(1);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_delay, unsigned long mls_duration);

/****************************************************************************************/
/* Schedule a delay to be executed by a subsequent co-yield. These calls do not yield 
   by themselves */

#define co_unschedule_delay() do {\
    CORC.mls_duration = 0;\
  } while (0)

#define co_schedule_delay(mls_duration_) do {\
    CORC.mls_start = mlb_millis();\
    CORC.mls_duration = (mls_duration_);\
  } while (0)

#define co_unschedule_inf_delay() do {\
    if (CORC.mls_duration == MLB_MLS_INF)\
      co_unschedule_delay();\
  } while (0)

#define co_schedule_min_delay(mls_duration_) do {\
    if (CORC.mls_duration == 0)\
      co_schedule_delay(mls_duration_);\
    else\
      CORC.mls_duration = MLB_MIN(CORC.mls_duration, (mls_duration_));\
  } while (0)

/****************************************************************************************/

#define co_wait_for_pin_inline(pin_ /* r */, target_state_ /* r */) do {\
    while (digitalRead(pin_) != (target_state_))\
      CO_YIELD__(1);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_wait_for_pin, uint8_t i_pin, uint8_t target_state);

/****************************************************************************************/

#define co_wait_for_stable_pin_inline(pin_ /* r */, target_state_ /* r */) do {\
    bool retry;\
    do\
    {\
      while (digitalRead(pin_) != (target_state_))\
        CO_YIELD__(1);\
      \
      retry = false;\
      for (CORC.mls_start = mlb_millis();\
           mlb_millis() - CORC.mls_start < MLB_STATE_DEBOUNCING_DELAY; )\
      {\
        if ((retry = digitalRead(pin_) != (target_state_)))\
          break;\
        CO_YIELD__(2);\
        retry = false;\
      }\
    } while (retry);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_wait_for_stable_pin, uint8_t i_pin, uint8_t target_state);

/****************************************************************************************/

#define co_wait_for_pin_lim_inline(pin_ /* r */, target_state_ /* r */,\
                                   mls_duration_ /* r */ , final_state_ /* w */) do {\
    (final_state_) = digitalRead(pin_);\
    if ((mls_duration_) == 0)\
      break;\
    \
    for (CORC.mls_start = mlb_millis(); mlb_millis() - CORC.mls_start < (mls_duration_); )\
    {\
      if ((final_state_) == (target_state_))\
        break;\
      \
      CO_YIELD__(1);\
      (final_state_) = digitalRead(pin_);\
    }\
  } while (0)

/* Note that 'co_wait_for_pin_lim_inline' does not require 'final_state_' to be 
   persistent */

CO_PROTOTYPE_NO_LOCALS(co_wait_for_pin_lim, 
                       uint8_t i_pin, uint8_t target_state, unsigned long mls_duration, 
                       uint8_t *mlb_restrict final_state);

/****************************************************************************************/

#define co_wait_for_stable_pin_lim_inline(pin_ /* r */, target_state_ /* r */,\
                                          mls_duration_ /* r */ , final_state_ /* w */) do {\
    (final_state_) = MLB_UNDEFINED;\
    if ((mls_duration_) == 0)\
      break;\
    \
    CORC.mls_start = mlb_millis();\
    bool done = false;\
    do\
    {\
      CORC.mls_local_start = mlb_millis();\
      uint8_t state;\
      while ((state = digitalRead(pin_)) != (target_state_))\
      {\
        if (mlb_millis() - CORC.mls_local_start >= MLB_STATE_DEBOUNCING_DELAY)\
          (final_state_) = state;\
        \
        if ((done = mlb_millis() - CORC.mls_start > (mls_duration_)))\
          break;\
        \
        CO_YIELD__(1);\
        done = false;\
      }\
      \
      if (done)\
        break;\
      \
      CORC.mls_local_start = mlb_millis();\
      while ((state = digitalRead(pin_)) == (target_state_))\
      {\
        if (mlb_millis() - CORC.mls_local_start >= MLB_STATE_DEBOUNCING_DELAY)\
        {\
          (final_state_) = state;\
          done = true;\
          break;\
        }\
        \
        if ((done = mlb_millis() - CORC.mls_start > (mls_duration_)))\
          break;\
        \
        CO_YIELD__(2);\
        done = false;\
      }\
    } while (!done);\
  } while (0)

CO_PROTOTYPE_NO_LOCALS(co_wait_for_stable_pin_lim, 
                       uint8_t i_pin, uint8_t target_state, unsigned long mls_duration, 
                       uint8_t *mlb_restrict final_state);

/****************************************************************************************/

#if CO_TRACK_STACK_USAGE || CO_REPORT_STACK_SIZE
  extern void *g_mlb_susg_printer;
  void mlb_co_susg_default_reporter(unsigned id, STD_ size_t usage);
  void mlb_co_ssize_default_reporter(unsigned id, STD_ size_t size);
#endif

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_ARDUINO_CO_H_ */
