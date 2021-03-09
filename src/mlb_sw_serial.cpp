#include "mlb_sw_serial.h"
#include "impl/mlb_wrapper.h"

#include <SoftwareSerial.h>

//char a[sizeof(SoftwareSerial)];
//char (*b)[sizeof(MlbSwSerial)] = &a;
mlb_static_assert(sizeof(MlbSwSerial) == sizeof(SoftwareSerial));

void mlb_sws_construct(MlbSwSerial *p, uint8_t receivePin, uint8_t transmitPin, 
                       bool inverse_logic /* = false */)
{
  assert(p != nullptr);
  new (p) SoftwareSerial(receivePin, transmitPin, inverse_logic);
}

void mlb_sws_destruct(MlbSwSerial *p)
{
  assert(p != nullptr);
  SoftwareSerial *d = reinterpret_cast<SoftwareSerial *>(p);
  d->~SoftwareSerial();
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbSwSerial
#define MLB_CPP_WRAPPER_CPP_CLASS SoftwareSerial

  MLB_CPP_WRAPPER_DEF(void, mlb_sws_begin, begin, long, speed)
  MLB_CPP_WRAPPER_DEF(void, mlb_sws_end, end)
  MLB_CPP_WRAPPER_DEF(bool, mlb_sws_is_ready, operator bool);
  MLB_CPP_WRAPPER_DEF(bool, mlb_sws_listen, listen)
  MLB_CPP_WRAPPER_DEF(bool, mlb_sws_is_listening, isListening)
  MLB_CPP_WRAPPER_DEF(bool, mlb_sws_stop_listening, stopListening)
  MLB_CPP_WRAPPER_DEF(bool, mlb_sws_overflow, overflow)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

