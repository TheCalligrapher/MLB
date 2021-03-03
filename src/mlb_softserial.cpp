#include "mlb_softserial.h"
#include "impl/mlb_wrapper.h"

#include <new>
#include <SoftwareSerial.h>

//char a[sizeof(SoftwareSerial)];
//char (*b)[sizeof(MlbSoftSerial)] = &a;
mlb_static_assert(sizeof(MlbSoftSerial) == sizeof(SoftwareSerial));

void softserial_construct(MlbSoftSerial *p, 
                          uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */)
{
  assert(p != nullptr);
  new (p) SoftwareSerial(receivePin, transmitPin, inverse_logic);
}

void softserial_destruct(MlbSoftSerial *p)
{
  assert(p != nullptr);
  SoftwareSerial *d = reinterpret_cast<SoftwareSerial *>(p);
  d->~SoftwareSerial();
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbSoftSerial
#define MLB_CPP_WRAPPER_CPP_CLASS SoftwareSerial

  MLB_CPP_WRAPPER_DEF(void, softserial_begin, begin, long, speed)
  MLB_CPP_WRAPPER_DEF(void, softserial_end, end)
  MLB_CPP_WRAPPER_DEF(bool, softserial_listen, listen)
  MLB_CPP_WRAPPER_DEF(bool, softserial_is_listening, isListening)
  MLB_CPP_WRAPPER_DEF(bool, softserial_stop_listening, stopListening)
  MLB_CPP_WRAPPER_DEF(bool, softserial_overflow, overflow)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

