#ifndef MLB_LIVE_BOOL_H_
#define MLB_LIVE_BOOL_H_

#include "base/mlb_config.h"

#include <stdbool.h>

#include "mlb_util.h"
#include "mlb_arduino_co.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbLiveBool
{
  bool v;
  unsigned n_flips;
  unsigned long duration, next_duration;
} MlbLiveBool;

/****************************************************************************************/

static inline bool mlb_lb_set(MlbLiveBool *lb, bool v)
{ 
  assert(lb != NULL);
  MLB_SWAP(bool, lb->v, v);
  lb->n_flips = 0;
  return v;
}

static inline bool mlb_lb_flip(MlbLiveBool *lb)
{ /* Does not change the running state or restart */
  assert(lb != NULL);
  lb->v = !lb->v;
  return !lb->v;
}

bool mlb_lb_set_for(MlbLiveBool *lb, bool v, unsigned long duration);

bool mlb_lb_pulse_train(MlbLiveBool *lb, bool v, 
                        unsigned long duration1, unsigned long duration2,
                        unsigned n_edges);

static inline bool mlb_lb_pulse(MlbLiveBool *lb, bool v, 
                                unsigned long duration1, unsigned long duration2)
{
  return mlb_lb_pulse_train(lb, v, duration1, duration2, UINT_MAX);
}

static inline bool mlb_lb_is(const MlbLiveBool *lb)
{
  assert(lb != NULL);
  return lb->v;
}

static inline const bool *mlb_lb_pbool(const MlbLiveBool *lb)
{
  assert(lb != NULL);
  return &lb->v;
}

/****************************************************************************************/

/* #define MLB_CO_IS_SUSPENDED 0x1 */

typedef struct MlbLiveBools
{
  MlbLiveBool *lbs;
  unsigned n;
  uint8_t flags;
} MlbLiveBools;

#define MLB_LBS_STATIC_INIT_STEADY(N) { (MlbLiveBool [N]) { 0 }, N }

#define MLB_LBS_STATIC_INIT(...)\
  { (MlbLiveBool []) { __VA_ARGS__ }, MLB_ARRAY_N(((MlbLiveBool []) { __VA_ARGS__ })) }

/****************************************************************************************/

static inline MlbLiveBool *mlb_lbs_at(const MlbLiveBools *mlb_lbs, unsigned i)
{
  assert(mlb_lbs != NULL && i < mlb_lbs->n);
  return &mlb_lbs->lbs[i];
}

static inline MlbLiveBools *mlb_lbs_post(MlbLiveBools *mlb_lbs)
{ /* Post-init routine (finalizer) to be applied to 'STATIC_INIT' initialized bools */
  return mlb_lbs;
}

static inline MlbLiveBools *mlb_lbs_init(MlbLiveBools *mlb_lbs, 
                                         MlbLiveBool *lbs, unsigned n)
{ 
  assert(mlb_lbs != NULL);
  *mlb_lbs = (MlbLiveBools) { lbs, n };
  /* Doesn't call 'mlb_lbs_post' */
  return mlb_lbs;
}

/****************************************************************************************/

CO_PROTOTYPE_DYNAMIC(mlb_lbs_execute, MlbLiveBools *mlb_lbs)
  unsigned long *starts;
CO_PROTOTYPE_END

#define MLB_LBS_DYN_SUSG__(n_) ((n_) * sizeof(unsigned long))
#define MLB_LBS_SUSG(n_)\
  (MLB_STRICT_ALIGN_UP(CO_SUSG(mlb_lbs_execute), alignof(unsigned long)) +\
   MLB_LBS_DYN_SUSG__(n_))

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_LIVE_BOOL_H_ */
