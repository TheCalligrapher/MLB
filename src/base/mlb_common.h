#ifndef MLB_COMMON_H_
#define MLB_COMMON_H_

#include "mlb_config.h"
#include "mlb_language.h"
#include "mlb_assert.h"

#if defined(__cplusplus) && MLB_USE_CPP_STD
  /* C++ */
  #include <climits>
  #include <cstddef>
  #include <cstdlib>
  #include <cstdint>
  #include <cstdarg>
  #include <new>
#elif defined(__cplusplus)
  /* C++ with C-style headers */
  #include <limits.h>
  #include <stddef.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <stdint.h>
  #include <stdarg.h>
  #include <new.h>
#else
  /* C */
  #include <limits.h>
  #include <stddef.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <stdint.h>
  #include <stdarg.h>
  #ifndef _MSC_VER
    #include <stdalign.h>
  #endif /* _MSC_VER */
#endif

#include "mlb_pp.h"

/****************************************************************************************/

#if defined(__cplusplus) && MLB_USE_CPP_STD
  #define STD_ std::
#else
  #define STD_
#endif

/****************************************************************************************/

#ifdef __cplusplus

  #define mlb_restrict

  #define MLB_INITIALIZER(T_, ...) (T_  __VA_ARGS__ )
  #define MLB_CONSTRUCT(T_, p_, ...) (new (p_) T_ __VA_ARGS__)
  #define MLB_DESTRUCT(T_, p_) ((p_)->~T_())

#else /* __cplusplus */

  #define mlb_restrict restrict

  #define MLB_INITIALIZER(T_, ...) ((T_) __VA_ARGS__)
  #define MLB_CONSTRUCT(T_, p_, ...) (*(p_) = (T_) __VA_ARGS__)
  #define MLB_DESTRUCT(T_, p_)

#endif /* __cplusplus */

/****************************************************************************************/

#ifndef NDEBUG
  #define MLB_DBG_ONLY(x) x
  #define MLB_DBG_ARG(x) x,
#else /* NDEBUG */
  #define MLB_DBG_ONLY(x)
  #define MLB_DBG_ARG(x)
#endif /* NDEBUG */

/****************************************************************************************/

#define MLB_ARRAY_N(a_) (sizeof (a_) / sizeof *(a_))

#define MLB_SET_N(a_, n_, v_)\
  do { for (STD_ size_t i = 0, n = (n_); i < n; ++i) (a_)[i] = (v_); } while (0)
#define MLB_ZERO_N(a_, n_) MLB_SET_N(a_, n_, 0)
  
/****************************************************************************************/

#define MLB_ABS(a_) ((a_) >= 0 ? (a_) : -(a_))
#define MLB_MIN(a_, b_) ((a_) <= (b_) ? (a_) : (b_))
#define MLB_MAX(a_, b_) ((a_) >= (b_) ? (a_) : (b_))

#define MLB_SWAP(T_, a_, b_) do {  T_ t = (a_); (a_) = (b_); (b_) = t; } while (0)

#define MLB_XOR(a_, b_) ((a_) ? !(b_) : (b_))
#define MLB_IMPLIES(a_, b_) ((a_) ? (b_) : true)

#define MLB_ALIGN_DELTA(v_, b_) ((v_) % (b_))
#define MLB_ALIGN_UP_DELTA(v_, b_) ((b_) - (((v_) + (b_) - 1u) % (b_) + 1u))

#define MLB_ALIGN(v_, b_) ((v_) / (b_) * (b_))
#define MLB_ALIGN_UP(v_, b_) (((v_) + (b_) - 1u) / (b_) * (b_))
#define MLB_IS_ALIGNED(v_, b_) ((v_) % (b_) == 0)
#define MLB_IS_ALIGNED_PTR(p_, b_) MLB_IS_ALIGNED((STD_ uintptr_t) p_, b_)

/****************************************************************************************/

#if MLB_STRICT_ALIGNMENT_REQUIRED

  #if defined(_MSC_VER) && !defined(__cplusplus)
    #define MLB_STRICT_ALIGN_MAX 8u
    mlb_static_assert(alignof(STD_ max_align_t) == MLB_STRICT_ALIGN_MAX);
    /* To make it usable under 'alignas' declared as '__declspec(align(#))'. Only literal 
       constants are supported by such implementation */
  #else
    #define MLB_STRICT_ALIGN_MAX alignof(STD_ max_align_t)
  #endif

  #define MLB_STRICT_ALIGN_DELTA(v_, b_) MLB_ALIGN_DELTA(v_, b_)
  #define MLB_STRICT_ALIGN_UP_DELTA(v_, b_) MLB_ALIGN_UP_DELTA(v_, b_)

  #define MLB_STRICT_ALIGN(v_, b_) MLB_ALIGN(v_, b_)
  #define MLB_STRICT_ALIGN_UP(v_, b_) MLB_ALIGN_UP(v_, b_)

  #define MLB_IS_STRICT_ALIGNED_PTR(p_, b_) MLB_IS_ALIGNED_PTR(p_, b_)

#else /* MLB_STRICT_ALIGNMENT_REQUIRED */

  #define MLB_STRICT_ALIGN_MAX ((STD_ size_t) 1u)

  #define MLB_STRICT_ALIGN_DELTA(v_, b_) 0u
  #define MLB_STRICT_ALIGN_UP_DELTA(v_, b_) 0u

  #define MLB_STRICT_ALIGN(v_, b_) (v_)
  #define MLB_STRICT_ALIGN_UP(v_, b_) (v_)

  #define MLB_IS_STRICT_ALIGNED_PTR(p_, b_) true

#endif /* MLB_STRICT_ALIGNMENT_REQUIRED */

#define MLB_STRICT_ALIGN_PTR(p_, b_)\
  ((void *) MLB_STRICT_ALIGN((STD_ uintptr_t) p_, b_))
#define MLB_STRICT_ALIGN_UP_PTR(p_, b_)\
  ((void *) MLB_STRICT_ALIGN_UP((STD_ uintptr_t) p_, b_))

/****************************************************************************************/

#endif /* MLB_COMMON_H_ */
