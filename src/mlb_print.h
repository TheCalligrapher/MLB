#ifndef MLB_PRINT_H_
#define MLB_PRINT_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

int mlb_print_available_for_write(void *p);
STD_ size_t mlb_print_write(void *p, const uint8_t *buffer, STD_ size_t size);
STD_ size_t mlb_print_write_c(void *p, uint8_t v);
STD_ size_t mlb_print_write_s(void *p, const char *str);

STD_ size_t mlb_print_s(void *p, const char *v);
STD_ size_t mlb_print_pgm(void *p, PGM_P v);
STD_ size_t mlb_print_c(void *p, char v);
STD_ size_t mlb_print_uc(void *p, unsigned char v);
STD_ size_t mlb_print_i(void *p, int v);
STD_ size_t mlb_print_ui(void *p, unsigned int v);
STD_ size_t mlb_print_l(void *p, long v);
STD_ size_t mlb_print_ul(void *p, unsigned long v);
STD_ size_t mlb_print_d(void *p, double v);
STD_ size_t mlb_print_dp(void *p, double v, int n);

STD_ size_t mlb_println_s(void *p, const char *v);
STD_ size_t mlb_println_pgm(void *p, PGM_P v);
STD_ size_t mlb_println_c(void *p, char v);
STD_ size_t mlb_println_uc(void *p, unsigned char v);
STD_ size_t mlb_println_i(void *p, int v);
STD_ size_t mlb_println_ui(void *p, unsigned int v);
STD_ size_t mlb_println_l(void *p, long v);
STD_ size_t mlb_println_ul(void *p, unsigned long v);
STD_ size_t mlb_println_d(void *p, double v);
STD_ size_t mlb_println_dp(void *p, double v, int n);

STD_ size_t mlb_println(void *p);

int mlb_print_get_write_error(void *p);
void mlb_print_clear_write_error(void *p);

C_LINKAGE_END

#endif /* MLB_PRINT_H_ */
