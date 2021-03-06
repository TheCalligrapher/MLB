#include "mlb_led.h"

void mlb_leds_attach_pins(MlbLeds *mlb_leds, const uint8_t pins[])
{
  assert(mlb_leds != NULL);
  for (unsigned i = 0; i < mlb_leds->n; ++i)
    mlb_led_attach_pin(mlb_leds_at(mlb_leds, i), pins[i]);
}

void mlb_leds_attach_pins_pgm(MlbLeds *mlb_leds, const uint8_t pins[])
{
  assert(mlb_leds != NULL);
  for (unsigned i = 0; i < mlb_leds->n; ++i, ++pins)
  {
    uint8_t i_pin = pgm_read_byte(pins);
    mlb_led_attach_pin(mlb_leds_at(mlb_leds, i), i_pin);
  }
}

void mlb_leds_attach_pbools(MlbLeds *mlb_leds, /* const */ bool *const bools[])
{
  assert(mlb_leds != NULL);
  for (unsigned i = 0; i < mlb_leds->n; ++i)
    mlb_led_attach_bool(mlb_leds_at(mlb_leds, i), bools[i]);
}

void mlb_leds_attach_bools(MlbLeds *mlb_leds, const bool bools[])
{
  assert(mlb_leds != NULL);
  for (unsigned i = 0; i < mlb_leds->n; ++i)
    mlb_led_attach_bool(mlb_leds_at(mlb_leds, i), &bools[i]);
}

void mlb_leds_attach_lbs(MlbLeds *mlb_leds, const MlbLiveBool lbs[])
{
  assert(mlb_leds != NULL);
  for (unsigned i = 0; i < mlb_leds->n; ++i)
    mlb_led_attach_lb(mlb_leds_at(mlb_leds, i), &lbs[i]);
}

void mlb_leds_attach_mlb_lbs(MlbLeds *mlb_leds, const MlbLiveBools *mlb_lbs)
{
  assert(mlb_leds != NULL);
  for (unsigned i = 0; i < mlb_leds->n; ++i)
    mlb_led_attach_lb(mlb_leds_at(mlb_leds, i), mlb_lbs_at(mlb_lbs, i));
}

CO_FUNCTION_DEFINITION(mlb_leds_execute)
{
  CO_BEGIN_DYNAMIC

  COL.states = CO_ALLOCA_T(MlbBool, COP.mlb_leds->n);
  MLB_SET_N(COL.states, COP.mlb_leds->n, MLB_BOOL_INVALID);

  for (;;)
  {
    if (!MLB_CO_SUSPENDABLE_IS_RUNNING(*COP.mlb_leds))
    {
      CO_YIELD();
      continue;
    }

    for (COL.i_led = 0; COL.i_led < COP.mlb_leds->n; ++COL.i_led)
    {
      MlbLed *led = mlb_leds_at(COP.mlb_leds, COL.i_led);
      if (led->v != NULL)
      {
        if (MLB_CMPSET(COL.states[COL.i_led], *led->v))
        {
          mlb_led_tick(led);
          CO_YIELD();
        }
      }
      else
        COL.states[COL.i_led] = MLB_BOOL_INVALID;
    }

    CO_YIELD(); /* In case all 'led->v' are null */
  }
  
  CO_END
}
