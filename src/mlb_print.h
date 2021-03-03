#ifndef MLB_PRINT_H_
#define MLB_PRINT_H_

#include "base/mlb_config.h"

#include <stdlib.h>
#include <stdint.h>

#include "mlb_util.h"

C_LINKAGE_BEGIN

int mlb_print_available_for_write(void *p);
size_t mlb_print_write(void *p, const uint8_t *buffer, size_t size);
size_t mlb_print_write_c(void *p, uint8_t v);
size_t mlb_print_write_s(void *p, const char *str);

size_t mlb_print_s(void *p, const char *v);
size_t mlb_print_pgm(void *p, PGM_P v);
size_t mlb_print_c(void *p, char v);
size_t mlb_print_uc(void *p, unsigned char v);
size_t mlb_print_i(void *p, int v);
size_t mlb_print_ui(void *p, unsigned int v);
size_t mlb_print_l(void *p, long v);
size_t mlb_print_ul(void *p, unsigned long v);
size_t mlb_print_d(void *p, double v);
size_t mlb_print_dp(void *p, double v, int n);

size_t mlb_println_s(void *p, const char *v);
size_t mlb_println_pgm(void *p, PGM_P v);
size_t mlb_println_c(void *p, char v);
size_t mlb_println_uc(void *p, unsigned char v);
size_t mlb_println_i(void *p, int v);
size_t mlb_println_ui(void *p, unsigned int v);
size_t mlb_println_l(void *p, long v);
size_t mlb_println_ul(void *p, unsigned long v);
size_t mlb_println_d(void *p, double v);
size_t mlb_println_dp(void *p, double v, int n);

size_t mlb_println(void *p);

int mlb_print_get_write_error(void *p);
void mlb_print_clear_write_error(void *p);

C_LINKAGE_END

#endif /* MLB_PRINT_H_ */
