#ifndef MLB_LANGUAGE_H_
#define MLB_LANGUAGE_H_

#include "mlb_config.h"

#if !defined(__cplusplus) && defined(_MSC_VER)
  typedef unsigned long long max_align_t;
  #define alignas(n_) __declspec(align(n_))
  #define alignof(p_) _Alignof(p_)
  #define restrict __restrict
  #define _Static_assert(c_, s_) static_assert(c_, s_)
#endif

#ifdef __cplusplus
  #define C_LINKAGE_BEGIN extern "C" {
  #define C_LINKAGE_END }
#else /* __cplusplus */
  #define C_LINKAGE_BEGIN
  #define C_LINKAGE_END
#endif /* __cplusplus */

#endif /* MLB_LANGUAGE_H_ */
