#ifndef MLB_ASSERT_H_
#define MLB_ASSERT_H_

#include "mlb_config.h"
#include "mlb_language.h"
#include "mlb_pp.h"

#if defined(__cplusplus) && MLB_USE_CPP_STD
  #if MLB_USE_STDLIB_ASSERT
    #include <cassert>
  #endif /* MLB_USE_STDLIB_ASSERT */
  #include <cstdlib>
#else /* MLB_USE_CPP_STD */
  #if MLB_USE_STDLIB_ASSERT
    #include <assert.h>
  #endif /* MLB_USE_STDLIB_ASSERT */
  #include <stdlib.h>
#endif /* MLB_USE_CPP_STD */

/****************************************************************************************/
/* Configuration supplied by the client translation unit after including 'mlb_assert.h'

   * 'MLB_ASSERT_STR_WRAPPER(x)' macro

/****************************************************************************************/

#ifdef __cplusplus
  #define mlb_static_assert(c_) static_assert(c_, "")
#else /* __cplusplus */
  #define mlb_static_assert(c_) _Static_assert(c_, "")
#endif /* !__cplusplus */

C_LINKAGE_BEGIN

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

#if !MLB_USE_STDLIB_ASSERT

  #undef assert
  #define assert(c) MLB_ASSERT(c)

#endif /* MLB_USE_STDLIB_ASSERT */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_ASSERT_H_ */
