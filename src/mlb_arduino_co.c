#include "mlb_arduino_co.h"
#include "mlb_print.h"

CO_FUNCTION_DEFINITION(co_delay)
{ /* Guarantees at least one 'CO_YIELD()', even if requested 'mls_duration' is zero */
  CO_BEGIN
  co_delay_inline(COP.mls_duration);
  CO_END
}

CO_FUNCTION_DEFINITION(co_wait_for_pin)
{
  CO_BEGIN
  co_wait_for_pin_inline(COP.i_pin, COP.target_state);
  CO_END
}

CO_FUNCTION_DEFINITION(co_wait_for_stable_pin)
{
  CO_BEGIN
  co_wait_for_stable_pin_inline(COP.i_pin, COP.target_state);
  CO_END
}

CO_FUNCTION_DEFINITION(co_wait_for_pin_lim)
{
  CO_BEGIN
  assert(COP.final_state != NULL);
  co_wait_for_pin_lim_inline(COP.i_pin, COP.target_state, COP.mls_duration, *COP.final_state);
  CO_END
}

CO_FUNCTION_DEFINITION(co_wait_for_stable_pin_lim)
{
  CO_BEGIN
  assert(COP.final_state != NULL);
  co_wait_for_stable_pin_lim_inline(COP.i_pin, COP.target_state, COP.mls_duration, *COP.final_state);
  CO_END
}

/****************************************************************************************/

#if CO_TRACK_STACK_USAGE || CO_REPORT_STACK_SIZE

void *g_mlb_susg_printer;

void mlb_co_susg_default_reporter(unsigned id, size_t usage)
{
  if (g_mlb_susg_printer != NULL)
  {
    mlb_print_ui(g_mlb_susg_printer, id);
    mlb_print_pgm(g_mlb_susg_printer, PSTR(" susg: ")); 
    mlb_println_ul(g_mlb_susg_printer, (unsigned long) usage);
  }
}

void mlb_co_ssize_default_reporter(unsigned id, size_t size)
{
  if (g_mlb_susg_printer != NULL)
  {
    mlb_print_ui(g_mlb_susg_printer, id);
    mlb_print_pgm(g_mlb_susg_printer, PSTR(" ssize: ")); 
    mlb_println_ul(g_mlb_susg_printer, (unsigned long) size);
  }
}

#endif /* CO_TRACK_STACK_USAGE || CO_REPORT_STACK_SIZE */
