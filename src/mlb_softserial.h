#ifndef MLB_SOFTSERIAL_H_
#define MLB_SOFTSERIAL_H_

#include "base/mlb_config.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "mlb_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbSoftSerial
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[48];
#else
  char fill[31];
#endif
} MlbSoftSerial;

void softserial_construct(MlbSoftSerial *p, 
                          uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */);
void softserial_destruct(MlbSoftSerial *p);

void softserial_begin(MlbSoftSerial *p, long speed);
void softserial_end(MlbSoftSerial *p);
bool softserial_listen(MlbSoftSerial *p);
bool softserial_is_listening(MlbSoftSerial *p);
bool softserial_stop_listening(MlbSoftSerial *p);
bool softserial_overflow(MlbSoftSerial *p);

/* Use 'mlb_stream' for 'Stream' functionality */
/* Use 'mlb_print' for 'Print' functionality */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SOFTSERIAL_H_ */
