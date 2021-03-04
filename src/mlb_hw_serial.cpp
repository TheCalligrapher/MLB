#include "mlb_hw_serial.h"
#include "impl/mlb_wrapper.h"

#undef NEED_FNS

#if defined(HAVE_HWSERIAL1) || defined (PIN_SERIAL1_TX)
MlbHwSerial *mlb_serial1(void)
{
  return (MlbHwSerial *) &Serial1;
}
#define NEED_FNS
#endif 

#if defined(HAVE_HWSERIAL2) || defined (PIN_SERIAL2_TX)
MlbHwSerial *mlb_serial2(void)
{
  return (MlbHwSerial *) &Serial2;
}
#define NEED_FNS
#endif /* HAVE_HWSERIAL2 */

#if defined(HAVE_HWSERIAL3) || defined (PIN_SERIAL3_TX)
MlbHwSerial *mlb_serial3(void)
{
  return (MlbHwSerial *) &Serial3;
}
#define NEED_FNS
#endif /* HAVE_HWSERIAL3 */

#if defined(HAVE_HWSERIAL4) || defined (PIN_SERIAL4_TX)
MlbHwSerial *mlb_serial4(void)
{
  return (MlbHwSerial *) &Serial4;
}
#define NEED_FNS
#endif /* HAVE_HWSERIAL4 */

#ifdef NEED_FNS

  #define MLB_CPP_WRAPPER_C_STRUCT MlbHwSerial
  #define MLB_CPP_WRAPPER_CPP_CLASS decltype(Serial1)

    MLB_CPP_WRAPPER_DEF(void, mlb_hw_serial_begin, begin, unsigned long, baud)

  #undef MLB_CPP_WRAPPER_C_STRUCT
  #undef MLB_CPP_WRAPPER_CPP_CLASS

#endif 


