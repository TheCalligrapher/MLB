#include "mlb_live_bool.h"

bool mlb_lb_set_for(MlbLiveBool *lb, bool v, unsigned long duration)
{ /* This is a restarting operation */
  assert(lb != NULL);
  
  if (duration == 0 || duration == MLB_MLS_INF)
    return mlb_lb_set(lb, MLB_XOR(v, duration == 0));

  MLB_SWAP(bool, lb->v, v);
  lb->n_flips = 1;
  lb->duration = duration;

  return v;
}

bool mlb_lb_pulse_train(MlbLiveBool *lb, bool v, 
                        unsigned long duration1, unsigned long duration2,
                        unsigned n_edges)
{ /* 'n_edges' - number of additonal flips after setting the value to 'v'.
     This is a restarting operation. */
  assert(lb != NULL);

  if (n_edges == 0 || duration1 == MLB_MLS_INF)
    return mlb_lb_set(lb, v);
    
  if (duration2 == MLB_MLS_INF)
    n_edges = 1;
    /* No need to consider 'duration2 == MLB_MLS_INF' as a special case anymore */

  if ((duration1 == 0) != (duration2 == 0))
  {
    if (duration1 == 0)
    {
      v = !v;
      duration1 = duration2;
      --n_edges;
    }

    if (n_edges == UINT_MAX || (n_edges % 2) == 0)
      return mlb_lb_set(lb, v);
    else
      return mlb_lb_set_for(lb, v, n_edges / 2 * duration1);
  }
  else if (duration1 == 0)
    return mlb_lb_set(lb, MLB_XOR(v, (n_edges % 2) != 0));

  MLB_SWAP(bool, lb->v, v);
  lb->n_flips = n_edges;
  lb->duration = duration1;
  lb->next_duration = duration2;

  return v;
}

/****************************************************************************************/

static inline bool mlb_lb_is_running(const MlbLiveBool *lb)
{
  assert(lb != NULL);
  return lb->n_flips > 0;
}

CO_FUNCTION_DEFINITION(mlb_lbs_execute)
{
  CO_BEGIN_DYNAMIC

  COL.starts = CO_ALLOCA_T(unsigned long, COP.mlb_lbs->n);
  MLB_SET_N(COL.starts, COP.mlb_lbs->n, MLB_MLS_INF);

  for (;;)
  {
    if (!MLB_CO_SUSPENDABLE_IS_RUNNING(*COP.mlb_lbs))
    {
      CO_YIELD();
      continue;
    }

    unsigned long min_remaining = MLB_MLS_INF;

    for (unsigned i = 0; i < COP.mlb_lbs->n; ++i)
    {
      MlbLiveBool *lb = mlb_lbs_at(COP.mlb_lbs, i);
      if (!mlb_lb_is_running(lb))
      { /* Not running */
        assert(COL.starts[i] == MLB_MLS_INF);
        continue;
      }

      if (COL.starts[i] == MLB_MLS_INF)
        COL.starts[i] = mlb_millis();

      assert(COL.starts[i] != MLB_MLS_INF);
      unsigned long passed = mlb_millis() - COL.starts[i];
      if (passed < lb->duration)
      {
        unsigned long remaining = lb->duration - passed;
        min_remaining = MLB_MIN(min_remaining, remaining);
        continue;
      }

      lb->v = !lb->v;
        
      if (lb->n_flips == UINT_MAX || --lb->n_flips > 0)
      {
        MLB_SWAP(unsigned long, lb->duration, lb->next_duration);
        if (lb->duration != MLB_MLS_INF)
        { /* Bool keeps running */
          COL.starts[i] = mlb_millis();
          min_remaining = MLB_MIN(min_remaining, lb->duration);
          continue;
        }
      }

      /* This bool just stopped */
      lb->n_flips = 0;
      assert(!mlb_lb_is_running(lb));
      COL.starts[i] = MLB_MLS_INF;
    }

    if (min_remaining < MLB_MLS_INF)
      co_delay_inline(min_remaining);
    else
      /* No bools running */
      CO_YIELD();
  }

  CO_END
}
