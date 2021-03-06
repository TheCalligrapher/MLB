#ifndef MLB_SERIAL_H_
#define MLB_SERIAL_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"
#include "mlb_print.h"

#include "impl/mlb_wrapper.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbSerial MlbSerial;

MlbSerial *mlb_serial(void);

void mlb_serial_begin(unsigned long baud);
bool mlb_serial_is_ready(void);

/* Use 'mlb_print' for 'Print' functionality */
/* Use 'mlb_stream' for 'Stream' functionality */
/* Or use wrappers below */

#define MLB_C_WRAPPER_GLOBAL mlb_serial()

  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_s, mlb_print_s, 
                                         const char *, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_pgm, mlb_print_pgm, 
                                         PGM_P, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_c, mlb_print_c, char, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_uc, mlb_print_uc, 
                                         unsigned char, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_i, mlb_print_i, int, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_ui, mlb_print_ui, 
                                         unsigned int, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_l, mlb_print_l, long, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_ul, mlb_print_ul, 
                                         unsigned long, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_d, mlb_print_d, 
                                         double, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serial_dp, mlb_print_dp, 
                                         double, v, int, n)

  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_s, mlb_println_s, 
                                         const char *, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_pgm, mlb_println_pgm, 
                                         PGM_P, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_c, mlb_println_c, 
                                         char, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_uc, mlb_println_uc, 
                                         unsigned char, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_i, mlb_println_i, 
                                         int, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_ui, mlb_println_ui, 
                                         unsigned int, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_l, mlb_println_l, 
                                         long, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_ul, mlb_println_ul, 
                                         unsigned long, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_d, mlb_println_d, 
                                         double, v)
  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln_dp, mlb_println_dp, 
                                         double, v, int, n)

  static inline MLB_C_GLOBAL_WRAPPER_DEF(STD_ size_t, mlb_serialln, mlb_println)

#undef MLB_C_WRAPPER_GLOBAL

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SERIAL_H_ */
