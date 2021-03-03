#include "mlb_print.h"
#include "impl/mlb_wrapper.h"

size_t mlb_print_pgm(void *p, PGM_P v)
{
  assert(p != nullptr);
  Print *d = reinterpret_cast<Print *>(p);
  return d->print(reinterpret_cast<const __FlashStringHelper *>(v));
}

size_t mlb_println_pgm(void *p, PGM_P v)
{
  assert(p != nullptr);
  Print *d = reinterpret_cast<Print *>(p);
  return d->println(reinterpret_cast<const __FlashStringHelper *>(v));
}

#define MLB_CPP_WRAPPER_C_STRUCT void
#define MLB_CPP_WRAPPER_CPP_CLASS Print

  MLB_CPP_WRAPPER_DEF(int, mlb_print_available_for_write, availableForWrite);
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_write, write, const uint8_t *, buffer, size_t, size);
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_write_u8, write, uint8_t, v);
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_write_s, write, const char *, str);

  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_s, print, const char *, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_c, print, char, v);
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_uc, print, unsigned char, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_i, print, int, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_ui, print, unsigned int, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_l, print, long, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_ul, print, unsigned long, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_d, print, double, v);
  MLB_CPP_WRAPPER_DEF(size_t, mlb_print_dp, print, double, v, int, n)

  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_s, println, const char *, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_c, println, char, v);
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_uc, println, unsigned char, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_i, println, int, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_ui, println, unsigned int, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_l, println, long, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_ul, println, unsigned long, v)
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_d, println, double, v);
  MLB_CPP_WRAPPER_DEF(size_t, mlb_println_dp, println, double, v, int, n)

  MLB_CPP_WRAPPER_DEF(size_t, mlb_println, println)

  MLB_CPP_WRAPPER_DEF(int, mlb_print_get_write_error, getWriteError);
  MLB_CPP_WRAPPER_DEF(void, mlb_print_clear_write_error, clearWriteError);

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

