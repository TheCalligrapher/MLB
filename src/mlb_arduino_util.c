#include "mlb_arduino_util.h"
#include "mlb_arduino_co.h"

#include "mlb_print.h"

/****************************************************************************************/

unsigned long g_mlb_current_millis;

unsigned long mlb_init(void)
{
  MLB_DBG_ONLY(g_mlb_assert_handler = mlb_assert_default_handler);
  CO_SUSG_ONLY(g_co_susg_reporter = mlb_co_susg_default_reporter);
  CO_REPORT_SSIZE_ONLY(g_co_ssize_reporter = mlb_co_ssize_default_reporter);
  return g_mlb_current_millis = millis();
}

/****************************************************************************************/

#ifndef NDEBUG

void *g_mlb_assert_printer;

void mlb_assert_default_handler(const char *arg, const char *file, int line)
{ /* Both 'arg' and 'file' are supposed to point to PROGMEM strings */
  if (g_mlb_assert_printer != NULL)
  {
    mlb_print_pgm(g_mlb_assert_printer, PSTR("Fail: ")); 
    mlb_println_pgm(g_mlb_assert_printer, arg);
    
    mlb_print_pgm(g_mlb_assert_printer, file); 
    mlb_print_pgm(g_mlb_assert_printer, PSTR(":"));
    mlb_println_i(g_mlb_assert_printer, line);
  }

  mlb_abort();
}

#endif /* NDEBUG */

void mlb_abort(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}
