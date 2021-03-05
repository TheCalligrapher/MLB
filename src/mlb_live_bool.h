#ifndef MLB_LIVE_BOOL_H_
#define MLB_LIVE_BOOL_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"
#include "mlb_arduino_co.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbLiveBool
{
  bool v;
  unsigned n_flips;
  unsigned long duration, next_duration;
} MlbLiveBool;

#define MLB_LB_INIT_OFF(on_) { 0 }
#define MLB_LB_INIT_STEADY(on_) { (on_) }
#define MLB_LB_INIT_ONE(duration_) { true, 1, (duration_) }
#define MLB_LB_INIT_OSC(hperiod_) { true, UINT_MAX, (hperiod_), (hperiod_) }

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

#define MLB_LBSA_NAME(name_) MLB_PP_CONCAT(name_, _lbsa)

#define MLB_LBS_OFF_N(linkage_, name_, n_)\
  static MlbLiveBool MLB_LBSA_NAME(name_)[n_] = { 0 };\
  linkage_ MlbLiveBools name_ = { MLB_LBSA_NAME(name_), n_ };

#define MLB_LBS(linkage_, name_, ...)\
  static MlbLiveBool MLB_LBSA_NAME(name_)[] = { __VA_ARGS__ };\
  linkage_ MlbLiveBools name_ =\
    { MLB_LBSA_NAME(name_), MLB_ARRAY_N(MLB_LBSA_NAME(name_)) };

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
  *mlb_lbs = MLB_INITIALIZER(MlbLiveBools, lbs, n);
  /* Doesn't call 'mlb_lbs_post' */
  return mlb_lbs;
}

/****************************************************************************************/

CO_PROTOTYPE_DYNAMIC(mlb_lbs_execute, MlbLiveBools *mlb_lbs)
{
  unsigned long *starts;
}
CO_PROTOTYPE_END

#define MLB_LBS_DYN_SUSG__(n_) ((n_) * sizeof(unsigned long))
#define MLB_LBS_SUSG(n_)\
  (MLB_STRICT_ALIGN_UP(COF_SUSG(mlb_lbs_execute), alignof(unsigned long)) +\
   MLB_LBS_DYN_SUSG__(n_))

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_LIVE_BOOL_H_ */
