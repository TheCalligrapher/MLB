#ifndef MLB_COMMON_H_
#define MLB_COMMON_H_

#include "mlb_config.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _MSC_VER
  #include <stdalign.h>
#endif /* _MSC_VER */

#include "mlb_pp.h"

/****************************************************************************************/

#if defined(_MSC_VER) && !defined(__cplusplus)
  typedef unsigned long long max_align_t;
  #define alignas(n_) __declspec(align(n_))
  #define alignof(p_) _Alignof(p_)
#endif

/****************************************************************************************/

#ifdef __cplusplus
  #define C_LINKAGE_BEGIN extern "C" {
  #define C_LINKAGE_END }
  #define mlb_restrict
#else /* __cplusplus */
  #define C_LINKAGE_BEGIN
  #define C_LINKAGE_END
  #define mlb_restrict restrict
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
  do { for (size_t i = 0, n = (n_); i < n; ++i) (a_)[i] = (v_); } while (0)
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

/****************************************************************************************/

#ifdef MLB_STRICT_ALIGNMENT_REQUIRED

  #if defined(_MSC_VER) && !defined(__cplusplus)
    #define MLB_STRICT_ALIGN_MAX 8u
    /* To make it usable under 'alignas' declared as '__declspec(align(#))' */
  #else
    #define MLB_STRICT_ALIGN_MAX alignof(max_align_t)
  #endif

  #define MLB_STRICT_ALIGN_DELTA(v_, b_) MLB_ALIGN_DELTA(v_, b_)
  #define MLB_STRICT_ALIGN_UP_DELTA(v_, b_) MLB_ALIGN_UP_DELTA(v_, b_)

  #define MLB_STRICT_ALIGN(v_, b_) MLB_ALIGN(v_, b_)
  #define MLB_STRICT_ALIGN_UP(v_, b_) MLB_ALIGN_UP(v_, b_)

#else /* MLB_STRICT_ALIGNMENT_REQUIRED */

  #define MLB_STRICT_ALIGN_MAX ((size_t) 1u)

  #define MLB_STRICT_ALIGN_DELTA(v_, b_) 0u
  #define MLB_STRICT_ALIGN_UP_DELTA(v_, b_) 0u

  #define MLB_STRICT_ALIGN(v_, b_) (v_)
  #define MLB_STRICT_ALIGN_UP(v_, b_) (v_)

#endif /* MLB_STRICT_ALIGNMENT_REQUIRED */

#define MLB_STRICT_ALIGN_PTR(p_, b_) ((void *) MLB_STRICT_ALIGN((uintptr_t) p_, b_))
#define MLB_STRICT_ALIGN_UP_PTR(p_, b_) ((void *) MLB_STRICT_ALIGN_UP((uintptr_t) p_, b_))

/****************************************************************************************/

#endif /* MLB_COMMON_H_ */
