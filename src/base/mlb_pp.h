#ifndef MLB_PP_H_
#define MLB_PP_H_

#include "mlb_config.h"

/****************************************************************************************/

#define MLB_PP_CONCAT_(a_, b_) a_##b_
#define MLB_PP_CONCAT(a_, b_) MLB_PP_CONCAT_(a_, b_)

#define MLB_PP_STR_(s_) #s_
#define MLB_PP_STR(s_) MLB_PP_STR_(s_)

#define MLB_PP_COMMA ,

#define MLB_PP_IDENTITY(...) __VA_ARGS__

#define MLB_PP_WRAP(...) (__VA_ARGS__)
/* Wraps its arguments into a pair of '()' */
#define MLB_PP_UNWRAP(x) MLB_PP_IDENTITY x
/* Removes external pair of '()' from the argument */

/****************************************************************************************/

#define MLB_ARG_N__(\
   _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10,\
  _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,\
  _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,\
  _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,\
  _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,\
  _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,\
  _61, _62, _63, N, ...) N

#define MLB_RSEQ_N__\
  62, 61, 60,\
  59, 58, 57, 56, 55, 54, 53, 52, 51, 50,\
  49, 48, 47, 46, 45, 44, 43, 42, 41, 40,\
  39, 38, 37, 36, 35, 34, 33, 32, 31, 30,\
  29, 28, 27, 26, 25, 24, 23, 22, 21, 20,\
  19, 18, 17, 16, 15, 14, 13, 12, 11, 10,\
  9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define MLB_PP_NARG_(...) MLB_ARG_N__(__VA_ARGS__)
#define MLB_PP_NARG(...) MLB_PP_NARG_(0, ##__VA_ARGS__, MLB_RSEQ_N__)

/****************************************************************************************/

#define MLB_INDEXED_INTERNAL__(f_, i_) f_##i_##__

/****************************************************************************************/
/* Extract an element from a parenthesized tuple */ 

#define MLB_AT_0__(x0_, ...) x0_
#define MLB_AT_1__(x0_, x1_, ...) x1_
#define MLB_AT_2__(x0_, x1_, x2_, ...) x2_
#define MLB_AT_3__(x0_, x1_, x2_, x3_, ...) x3_
#define MLB_AT_4__(x0_, x1_, x2_, x3_, x4_, ...) x4_
#define MLB_AT_5__(x0_, x1_, x2_, x3_, x4_, x5_, ...) x5_

#define MLB_PP_AT(p_, i_) MLB_INDEXED_INTERNAL__(MLB_AT_, i_) p_
/* 'p_' is expecxted to be an '()'-tuple */

/****************************************************************************************/
/* Internal iterator 

     a0 a1 a2 ... an -> f(a0) f(a1) f(a2) ... f(an)
     a0 a1 a2 ... an -> ff(a0) fm(a1) fm(a2) ... fm(an)
*/

/* Middle (and last) application */
#define MLB_APPLY_M_U_0__(fm_) 
#define MLB_APPLY_M_U_1__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_0__(fm_)
#define MLB_APPLY_M_U_2__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_1__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_3__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_2__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_4__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_3__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_5__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_4__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_6__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_5__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_7__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_6__(fm_, ##__VA_ARGS__) 
#define MLB_APPLY_M_U_8__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_7__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_9__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_8__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_10__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_9__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_11__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_10__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_12__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_11__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_13__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_12__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_14__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_13__(fm_, ##__VA_ARGS__) 
#define MLB_APPLY_M_U_15__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_14__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_U_16__(fm_, a_, ...) fm_(a_) MLB_APPLY_M_U_15__(fm_, ##__VA_ARGS__)

/* First application */
#define MLB_APPLY_FM_U_0__(ff_, fm_) 
#define MLB_APPLY_FM_U_1__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_0__(fm_)
#define MLB_APPLY_FM_U_2__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_1__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_3__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_2__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_4__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_3__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_5__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_4__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_6__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_5__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_7__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_6__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_8__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_7__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_9__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_8__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_10__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_9__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_11__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_10__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_12__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_11__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_13__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_12__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_14__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_13__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_15__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_14__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_U_16__(ff_, fm_, a_, ...) ff_(a_) MLB_APPLY_M_U_15__(fm_, ##__VA_ARGS__)

#define MLB_APPLY_FM_U_I__(i_, ...) MLB_INDEXED_INTERNAL__(MLB_APPLY_FM_U_, i_)(__VA_ARGS__)

#define MLB_PP_APPLY_FM_U(ff_, fm_, ...) MLB_APPLY_FM_U_I__(MLB_PP_NARG(__VA_ARGS__), ff_, fm_, ##__VA_ARGS__)
#define MLB_PP_APPLY_U(f_, ...) MLB_PP_APPLY_FM_U(f_, f_, ##__VA_ARGS__)

/****************************************************************************************/
/* Pairwise internal iterator

     a0 a1 a2 ... an -> f(a0, a1) f(a2, a3) ... f(an-1, an)
     a0 a1 a2 ... an -> ff(a0, a1) fm(a2, a3) ... fm(an-1, an)
*/

/* Middle (and last) application */
#define MLB_APPLY_M_B_0__(fm_) 
#define MLB_APPLY_M_B_2__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_0__(fm_)
#define MLB_APPLY_M_B_4__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_2__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_B_6__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_4__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_B_8__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_6__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_B_10__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_8__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_B_12__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_10__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_B_14__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_12__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_M_B_16__(fm_, a_, b_, ...) fm_(a_, b_) MLB_APPLY_M_B_14__(fm_, ##__VA_ARGS__)

/* First application */
#define MLB_APPLY_FM_B_0__(ff_, fm_) 
#define MLB_APPLY_FM_B_2__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_0__(fm_)
#define MLB_APPLY_FM_B_4__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_2__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_B_6__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_4__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_B_8__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_6__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_B_10__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_8__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_B_12__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_10__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_B_14__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_12__(fm_, ##__VA_ARGS__)
#define MLB_APPLY_FM_B_16__(ff_, fm_, a_, b_, ...) ff_(a_, b_) MLB_APPLY_M_B_14__(fm_, ##__VA_ARGS__)

#define MLB_APPLY_FM_B_I__(i_, ...) MLB_INDEXED_INTERNAL__(MLB_APPLY_FM_B_, i_)(__VA_ARGS__)

#define MLB_PP_APPLY_FM_B(ff_, fm_, ...) MLB_APPLY_FM_B_I__(MLB_PP_NARG(__VA_ARGS__), ff_, fm_, ##__VA_ARGS__)
#define MLB_PP_APPLY_B(f_, ...) MLB_PP_APPLY_FM_B(f_, f_, ##__VA_ARGS__)

/****************************************************************************************/
/* Left fold for a binary 'f'

     a0 a1 a2 ... an -> f(...f(f(a0, a1), a2), ...), an)
*/

#define MLB_FOLD_L_2__(f_, a_, b_) f_(a_, b_)
#define MLB_FOLD_L_3__(f_, a_, b_, ...) MLB_FOLD_L_2__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_4__(f_, a_, b_, ...) MLB_FOLD_L_3__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_5__(f_, a_, b_, ...) MLB_FOLD_L_4__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_6__(f_, a_, b_, ...) MLB_FOLD_L_5__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_7__(f_, a_, b_, ...) MLB_FOLD_L_6__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_8__(f_, a_, b_, ...) MLB_FOLD_L_7__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_9__(f_, a_, b_, ...) MLB_FOLD_L_8__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_10__(f_, a_, b_, ...) MLB_FOLD_L_9__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_11__(f_, a_, b_, ...) MLB_FOLD_L_10__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_12__(f_, a_, b_, ...) MLB_FOLD_L_11__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_13__(f_, a_, b_, ...) MLB_FOLD_L_12__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_14__(f_, a_, b_, ...) MLB_FOLD_L_13__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_15__(f_, a_, b_, ...) MLB_FOLD_L_14__(f_, f_(a_, b_), ##__VA_ARGS__)
#define MLB_FOLD_L_16__(f_, a_, b_, ...) MLB_FOLD_L_15__(f_, f_(a_, b_), ##__VA_ARGS__)

#define MLB_FOLD_L_I__(i_, ...) MLB_INDEXED_INTERNAL__(MLB_FOLD_L_, i_)(__VA_ARGS__)

#define MLB_PP_FOLD_L(f_, ...) MLB_FOLD_L_I__(MLB_PP_NARG(__VA_ARGS__), f_, ##__VA_ARGS__)

/****************************************************************************************/

#endif /* MLB_PP_H_ */
