#ifndef MLB_ASSERT_H_
#define MLB_ASSERT_H_

#include "mlb_config.h"

#ifdef MLB_USE_STDLIB_ASSERT
  #include <assert.h>
#endif /* MLB_USE_STDLIB_ASSERT */

#include <stdlib.h>

/****************************************************************************************/
/* Configuration supplied by the client translation unit:

   * 'MLB_ASSERT_STR_WRAPPER(x)' macro

/****************************************************************************************/

#ifdef __cplusplus
  #define mlb_static_assert(c) static_assert(c, "")
#else /* __cplusplus */
  #define mlb_static_assert(c) _Static_assert(c, "")
#endif /* !__cplusplus */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************************************************************************************/

#ifndef NDEBUG

  extern void (*g_mlb_assert_handler)(const char *arg, const char *file, int line);
  void mlb_assert(const char *arg, const char *file, int line);

  #define MLB_ASSERT_STR_WRAPPER(str) str
  #define MLB_ASSERT(c) ((c) ? ((void) 0) : \
    mlb_assert(MLB_ASSERT_STR_WRAPPER(MLB_PP_STR(c)), MLB_ASSERT_STR_WRAPPER(__FILE__), __LINE__))

#else /* NDEBUG */

  #define MLB_ASSERT(c) ((void) 0)

#endif  /* NDEBUG */

#ifndef MLB_USE_STDLIB_ASSERT

  #undef assert
  #define assert(c) MLB_ASSERT(c)

#endif /* MLB_USE_STDLIB_ASSERT */

/****************************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MLB_ASSERT_H_ */