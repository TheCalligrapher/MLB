#ifndef MLB_UTIL_H_
#define MLB_UTIL_H_

#include "base/mlb_config.h"

#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <Arduino.h>

#include "base/mlb_assert.h"
#include "base/mlb_pp.h"
#include "base/mlb_common.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

#define UNDEFINED 0xFF
/* To accompany 'LOW' and 'HIGH' */
mlb_static_assert(UNDEFINED != LOW && UNDEFINED != HIGH);

/****************************************************************************************/

#undef MLB_ASSERT_STR_WRAPPER
#define MLB_ASSERT_STR_WRAPPER(str) PSTR(str)

/****************************************************************************************/

#define MLB_SET_BITS(src, bits) ((src) | (bits))
#define MLB_RESET_BITS(src, bits) ((src) & ~(bits))
#define MLB_SET_RESET_BITS(src, bits, set) ((set) ? MLB_SET_BITS(src, bits) : MLB_RESET_BITS(src, bits))
#define MLB_SET_MASK_BITS(src, mask, bits) (((src) & ~(mask)) | ((mask) & (bits)))

#define MLB_IS_ANY_BIT_SET(src, bits) (((src) & (bits)) != 0)
#define MLB_IS_ALL_BITS_SET(src, bits) (((src) & (bits)) == (bits))
#define MLB_IS_BIT_SET(src, bits) MLB_IS_ALL_BITS_SET(src, bits)

#define MLB_CMPSET(dst, src) ((dst) != (src) ? (dst) = (src), true : false)
#define MLB_CMPSET_FLAG(dst, flag) (((dst) & (flag)) == 0 ? (dst) |= (flag), true : false)
#define MLB_CONSUME_FLAG(dst, flag) (((dst) & (flag)) != 0 ? (dst) &= ~(flag), true : false)

static inline uint8_t mlb_bool_to_hl(bool b)
{
  return b ? HIGH : LOW;
}

static inline bool mlb_hl_to_bool(uint8_t hl)
{
  return hl == LOW;
}

/****************************************************************************************/

#define MLB_CO_IS_SUSPENDED 0x1

#define MLB_CO_SUSPENDABLE_START(p)((p).flags = MLB_RESET_BITS((p).flags, MLB_CO_IS_SUSPENDED))
#define MLB_CO_SUSPENDABLE_STOP(p) ((p).flags = MLB_SET_BITS((p).flags, MLB_CO_IS_SUSPENDED))
#define MLB_CO_SUSPENDABLE_IS_RUNNING(p) (!MLB_IS_BIT_SET((p).flags, MLB_CO_IS_SUSPENDED))

/****************************************************************************************/

typedef uint8_t MlbBool;

#define MLB_BOOL_INVALID ((MlbBool) -1)

/****************************************************************************************/

#define PROGMEM_STRUCT(T, ...) ({ static const T s PROGMEM = __VA_ARGS__; &s; })
#define PROGMEM_ARRAY(T, ...) ({ static const T a[] PROGMEM = __VA_ARGS__; (const T *) a; })

/****************************************************************************************/

#ifndef NDEBUG
  extern void *g_mlb_assert_printer;
  void mlb_assert_default_handler(const char *arg, const char *file, int line);
#endif /* NDEBUG */

void mlb_abort(void);

/****************************************************************************************/

#define MLB_MLS_001SECOND  10ul
#define MLB_MLS_01SECOND   100ul
#define MLB_MLS_1SECOND    1000ul
#define MLB_MLS_1MINUTE    60000ul
#define MLB_MLS_1HOUR      3600000ul
#define MLB_MLS_INF        ULONG_MAX

extern unsigned long g_mlb_current_millis;

unsigned long mlb_init(void);

static inline unsigned long mlb_tick(void)
{
  return g_mlb_current_millis = millis();
}

static inline unsigned long mlb_millis(void)
{
  return g_mlb_current_millis;
}

#define MLB_CMPSET_AGE(timestamp, age)\
  ((mlb_millis() - (timestamp)) > (age) ? timestamp = mlb_millis(), true : false)

/****************************************************************************************/

typedef unsigned MlbUis;

#define MLB_UIS_INF UINT_MAX
#define MLB_UIS_MUL 10ul
#define MLB_UIS_MAX ((UINT_MAX - 1) * MLB_UIS_MUL)
/* UI time units are measured in 0.01 seconds */

static inline MlbUis mlb_millis_to_uis(unsigned long millis)
{
  return millis != MLB_MLS_INF ? (MlbUis) (millis / MLB_UIS_MUL) : MLB_UIS_INF;
}

static inline unsigned long mlb_uis_to_millis(MlbUis ui)
{
  return ui != MLB_UIS_INF ? (unsigned long) ui * MLB_UIS_MUL : MLB_MLS_INF; 
}

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_UTIL_H_ */
