#ifndef MLB_WRAPPER_H_
#define MLB_WRAPPER_H_

#include "../base/mlb_config.h"
#include "../base/mlb_pp.h"

#define MLB_2_AB__(a_, b_) a_ b_
#define MLB_2_CAB__(a_, b_) , a_ b_
#define MLB_2_B__(a_, b_) b_
#define MLB_2_CB__(a_, b_) , b_

#define MLB_CPAIR__(...) MLB_APPLY_2(MLB_2_CAB__, ##__VA_ARGS__)
/* Includes leading comma for non-empty result */

#define MLB_PAIR__(...) MLB_APPLY_FM_2(MLB_2_AB__, MLB_2_CAB__, ##__VA_ARGS__)
/* Doesn't include leading comma */

#define MLB_CEVEN__(...) MLB_APPLY_2(MLB_2_CB__, ##__VA_ARGS__)
/* Includes leading comma for non-empty result */

#define MLB_EVEN__(...) MLB_APPLY_FM_2(MLB_2_B__, MLB_2_CB__, ##__VA_ARGS__)
/* Doesn't include leading comma */

#define MLB_CPP_WRAPPER_DEF(type_, c_name_, cpp_name_, ...)\
  type_ c_name_(MLB_CPP_WRAPPER_C_STRUCT *p MLB_CPAIR__(__VA_ARGS__)) {\
    assert(p != nullptr);\
    MLB_CPP_WRAPPER_CPP_CLASS *d = reinterpret_cast<MLB_CPP_WRAPPER_CPP_CLASS *>(p);\
    return d->cpp_name_(MLB_EVEN__(__VA_ARGS__));\
  }
/* Expects 'MLB_CPP_WRAPPER_C_STRUCT' and 'MLB_CPP_WRAPPER_CPP_CLASS' */

#define MLB_CPP_WRAPPER_CONST_DEF(type_, c_name_, cpp_name_, ...)\
  type_ c_name_(const MLB_CPP_WRAPPER_C_STRUCT *p MLB_CPAIR__(__VA_ARGS__)) {\
    assert(p != nullptr);\
    const MLB_CPP_WRAPPER_CPP_CLASS *d = reinterpret_cast<const MLB_CPP_WRAPPER_CPP_CLASS *>(p);\
    return d->cpp_name_(MLB_EVEN__(__VA_ARGS__));\
  }
/* Expects 'MLB_CPP_WRAPPER_C_STRUCT' and 'MLB_CPP_WRAPPER_CPP_CLASS' */

#define MLB_CPP_GLOBAL_WRAPPER_DEF(type_, c_name_, cpp_name_, ...)\
  type_ c_name_(MLB_PAIR__(__VA_ARGS__)) {\
    return (MLB_CPP_WRAPPER_GLOBAL).cpp_name_(MLB_EVEN__(__VA_ARGS__));\
  }
/* Expects 'MLB_CPP_WRAPPER_GLOBAL' */

#define MLB_C_GLOBAL_WRAPPER_DEF(type_, wrapper_name_, wrapped_name_, ...)\
  type_ wrapper_name_(MLB_PAIR__(__VA_ARGS__)) {\
    return wrapped_name_((MLB_C_WRAPPER_GLOBAL) MLB_CEVEN__(__VA_ARGS__));\
  }
/* Expects 'MLB_C_WRAPPER_GLOBAL' */

#endif /* MLB_WRAPPER_H_ */
