#ifndef MLB_PP_H_
#define MLB_PP_H_

#include "mlb_config.h"

#define MLB_PP_CONCAT_(a_, b_) a_##b_
#define MLB_PP_CONCAT(a_, b_) MLB_PP_CONCAT_(a_, b_)

#define MLB_PP_STR_(s_) #s_
#define MLB_PP_STR(s_) MLB_PP_STR_(s_)

#define MLB_PP_COMMA ,

/****************************************************************************************/

#define MLB_PP_INVOKE(m_, args_) m_ args_
#define MLB_PP_INVOKE_0(m_, args_) m_ args_
#define MLB_PP_INVOKE_1(m_, args_) m_ args_
#define MLB_PP_INVOKE_2(m_, args_) m_ args_
#define MLB_PP_INVOKE_3(m_, args_) m_ args_
#define MLB_PP_INVOKE_4(m_, args_) m_ args_
#define MLB_PP_INVOKE_5(m_, args_) m_ args_
#define MLB_PP_INVOKE_6(m_, args_) m_ args_
#define MLB_PP_INVOKE_7(m_, args_) m_ args_
#define MLB_PP_INVOKE_8(m_, args_) m_ args_
#define MLB_PP_INVOKE_9(m_, args_) m_ args_
#define MLB_PP_INVOKE_10(m_, args_) m_ args_
#define MLB_PP_INVOKE_11(m_, args_) m_ args_
#define MLB_PP_INVOKE_12(m_, args_) m_ args_
#define MLB_PP_INVOKE_13(m_, args_) m_ args_
#define MLB_PP_INVOKE_14(m_, args_) m_ args_
#define MLB_PP_INVOKE_15(m_, args_) m_ args_
#define MLB_PP_INVOKE_16(m_, args_) m_ args_

#define MLB_PP_ARG_N(\
   _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10,\
  _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,\
  _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,\
  _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,\
  _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,\
  _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,\
  _61, _62, _63, N, ...) N

#define MLB_PP_RSEQ_N\
  62, 61, 60,\
  59, 58, 57, 56, 55, 54, 53, 52, 51, 50,\
  49, 48, 47, 46, 45, 44, 43, 42, 41, 40,\
  39, 38, 37, 36, 35, 34, 33, 32, 31, 30,\
  29, 28, 27, 26, 25, 24, 23, 22, 21, 20,\
  19, 18, 17, 16, 15, 14, 13, 12, 11, 10,\
  9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define MLB_PP_NARG(...) MLB_PP_INVOKE(MLB_PP_ARG_N, (0, ##__VA_ARGS__, MLB_PP_RSEQ_N))

/****************************************************************************************/

/* Middle (and last) application */
#define MLB_APPLY_M_1_0(mm_) 
#define MLB_APPLY_M_1_1(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_1(MLB_APPLY_M_1_0, (mm_))
#define MLB_APPLY_M_1_2(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_2(MLB_APPLY_M_1_1, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_3(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_3(MLB_APPLY_M_1_2, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_4(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_4(MLB_APPLY_M_1_3, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_5(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_5(MLB_APPLY_M_1_4, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_6(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_6(MLB_APPLY_M_1_5, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_7(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_7(MLB_APPLY_M_1_6, (mm_, ##__VA_ARGS__)) 
#define MLB_APPLY_M_1_8(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_8(MLB_APPLY_M_1_7, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_9(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_9(MLB_APPLY_M_1_8, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_10(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_10(MLB_APPLY_M_1_9, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_11(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_11(MLB_APPLY_M_1_10, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_12(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_12(MLB_APPLY_M_1_11, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_13(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_13(MLB_APPLY_M_1_12, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_14(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_14(MLB_APPLY_M_1_13, (mm_, ##__VA_ARGS__)) 
#define MLB_APPLY_M_1_15(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_15(MLB_APPLY_M_1_14, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_1_16(mm_, a_, ...) mm_(a_) MLB_PP_INVOKE_16(MLB_APPLY_M_1_15, (mm_, ##__VA_ARGS__))

/* First application */
#define MLB_APPLY_FM_1_0(mf_, mm_) 
#define MLB_APPLY_FM_1_1(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_1(MLB_APPLY_M_1_0, (mm_))
#define MLB_APPLY_FM_1_2(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_2(MLB_APPLY_M_1_1, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_3(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_3(MLB_APPLY_M_1_2, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_4(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_4(MLB_APPLY_M_1_3, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_5(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_5(MLB_APPLY_M_1_4, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_6(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_6(MLB_APPLY_M_1_5, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_7(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_7(MLB_APPLY_M_1_6, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_8(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_8(MLB_APPLY_M_1_7, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_9(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_2(MLB_APPLY_M_1_8, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_10(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_3(MLB_APPLY_M_1_9, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_11(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_4(MLB_APPLY_M_1_10, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_12(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_5(MLB_APPLY_M_1_11, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_13(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_6(MLB_APPLY_M_1_12, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_14(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_7(MLB_APPLY_M_1_13, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_15(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_8(MLB_APPLY_M_1_14, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_1_16(mf_, mm_, a_, ...) mf_(a_) MLB_PP_INVOKE_2(MLB_APPLY_M_1_15, (mm_, ##__VA_ARGS__))

#define MLB_APPLY_FM_1_I(i_, ...) MLB_PP_INVOKE(MLB_PP_CONCAT(MLB_APPLY_FM_1_, i_), (__VA_ARGS__))
#define MLB_APPLY_FM_1(mf_, mm_, ...) MLB_APPLY_FM_1_I(MLB_PP_NARG(__VA_ARGS__), mf_, mm_, ##__VA_ARGS__)

#define MLB_APPLY_1(m_, ...) MLB_APPLY_FM_1(m_, m_, ##__VA_ARGS__)

/****************************************************************************************/

/* Middle (and last) application */
#define MLB_APPLY_M_2_0(mm_) 
#define MLB_APPLY_M_2_2(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_2(MLB_APPLY_M_2_0, (mm_))
#define MLB_APPLY_M_2_4(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_4(MLB_APPLY_M_2_2, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_2_6(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_6(MLB_APPLY_M_2_4, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_2_8(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_8(MLB_APPLY_M_2_6, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_2_10(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_10(MLB_APPLY_M_2_8, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_2_12(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_12(MLB_APPLY_M_2_10, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_2_14(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_14(MLB_APPLY_M_2_12, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_M_2_16(mm_, a_, b_, ...) mm_(a_, b_) MLB_PP_INVOKE_16(MLB_APPLY_M_2_14, (mm_, ##__VA_ARGS__))

/* First application */
#define MLB_APPLY_FM_2_0(mf_, mm_) 
#define MLB_APPLY_FM_2_2(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_2(MLB_APPLY_M_2_0, (mm_))
#define MLB_APPLY_FM_2_4(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_4(MLB_APPLY_M_2_2, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_2_6(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_6(MLB_APPLY_M_2_4, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_2_8(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_8(MLB_APPLY_M_2_6, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_2_10(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_10(MLB_APPLY_M_2_8, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_2_12(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_12(MLB_APPLY_M_2_10, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_2_14(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_14(MLB_APPLY_M_2_12, (mm_, ##__VA_ARGS__))
#define MLB_APPLY_FM_2_16(mf_, mm_, a_, b_, ...) mf_(a_, b_) MLB_PP_INVOKE_16(MLB_APPLY_M_2_14, (mm_, ##__VA_ARGS__))

#define MLB_APPLY_FM_2_I(i_, ...) MLB_PP_INVOKE(MLB_PP_CONCAT(MLB_APPLY_FM_2_, i_), (__VA_ARGS__))
#define MLB_APPLY_FM_2(mf_, mm_, ...) MLB_APPLY_FM_2_I(MLB_PP_NARG(__VA_ARGS__), mf_, mm_, ##__VA_ARGS__)

#define MLB_APPLY_2(m_, ...) MLB_APPLY_FM_2(m_, m_, ##__VA_ARGS__)

/****************************************************************************************/

#endif /* MLB_PP_H_ */
