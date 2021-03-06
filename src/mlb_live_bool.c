#include "mlb_live_bool.h"

bool mlb_lb_set_for(MlbLiveBool *lb, bool v, unsigned long mls_duration)
{ /* Monostable bool. This is a restarting operation */
  assert(lb != NULL);
  
  if (mls_duration == 0 || mls_duration == MLB_MLS_INF)
    return mlb_lb_set(lb, MLB_XOR(v, mls_duration == 0));

  MLB_SWAP(bool, lb->v, v);
  lb->n_flips = 1;
  lb->mls_duration = mls_duration;
  lb->mls_start = MLB_MLS_INF;

  return v;
}

bool mlb_lb_pulse_train(MlbLiveBool *lb, bool v, 
                        unsigned long mls_duration1, unsigned long mls_duration2,
                        unsigned n_edges)
{ /* 'n_edges' - number of additonal flips after setting the value to 'v'.
     This is a restarting operation. */
  assert(lb != NULL);

  if (n_edges == 0 || mls_duration1 == MLB_MLS_INF)
    /* Steady state */
    return mlb_lb_set(lb, v);
    
  if (mls_duration2 == MLB_MLS_INF)
    n_edges = 1;
    /* No need to consider 'mls_duration2 == MLB_MLS_INF' as a special case anymore */

  if ((mls_duration1 == 0) != (mls_duration2 == 0))
  {
    if (mls_duration1 == 0)
    {
      v = !v;
      mls_duration1 = mls_duration2;
      --n_edges;
    }

    if (n_edges == UINT_MAX || (n_edges % 2) == 0)
      /* Steady state */
      return mlb_lb_set(lb, v);
    else
      /* Monostable state */
      return mlb_lb_set_for(lb, v, n_edges / 2 * mls_duration1);
  }
  else if (mls_duration1 == 0)
    /* Steady state */
    return mlb_lb_set(lb, MLB_XOR(v, (n_edges % 2) != 0));

  MLB_SWAP(bool, lb->v, v);
  lb->n_flips = n_edges;
  lb->mls_duration = mls_duration1;
  lb->mls_next_duration = mls_duration2;
  lb->mls_start = MLB_MLS_INF;

  return v;
}

unsigned long mlb_lb_tick(MlbLiveBool *lb)
{ 
  assert(lb != NULL);

  if (!mlb_lb_is_running(lb))
    return MLB_MLS_INF;

  if (lb->mls_start == MLB_MLS_INF)
  {
    lb->mls_start = mlb_millis();
    return lb->mls_duration;
  }

  unsigned long mls_passed = mlb_millis() - lb->mls_start;
  if (mls_passed < lb->mls_duration)
    return lb->mls_duration - mls_passed;

  lb->v = !lb->v;
        
  if (lb->n_flips == UINT_MAX || --lb->n_flips > 0)
  {
    MLB_SWAP(unsigned long, lb->mls_duration, lb->mls_next_duration);
    if (lb->mls_duration != MLB_MLS_INF)
    { /* Bool keeps running */
      lb->mls_start = mlb_millis();
      return lb->mls_duration;
    }
  }

  /* This bool just stopped */
  lb->n_flips = 0;
  assert(!mlb_lb_is_running(lb));
  return MLB_MLS_INF;
}

/****************************************************************************************/

CO_FUNCTION_DEFINITION(mlb_lbs_execute)
{
  CO_BEGIN

  for (;;)
  {
    if (!MLB_CO_SUSPENDABLE_IS_RUNNING(*COP.mlb_lbs))
    {
      CO_YIELD();
      continue;
    }

    unsigned long mls_min_remaining = MLB_MLS_INF;

    for (unsigned i = 0; i < COP.mlb_lbs->n; ++i)
    {
      MlbLiveBool *lb = mlb_lbs_at(COP.mlb_lbs, i);
      unsigned long mls_remaining = mlb_lb_tick(lb);
      mls_min_remaining = MLB_MIN(mls_min_remaining, mls_remaining);
    }

    if (mls_min_remaining < MLB_MLS_INF)
      co_delay_inline(mls_min_remaining);
    else
      /* No bools running */
      CO_YIELD();
  }

  CO_END
}
