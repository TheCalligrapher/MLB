#ifndef MLB_SW_SERIAL_H_
#define MLB_SW_SERIAL_H_

#include "base/mlb_config.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "mlb_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbSwSerial
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[48];
#else
  char fill[31];
#endif
} MlbSwSerial;

void mlb_sw_serial_construct(MlbSwSerial *p, 
                             uint8_t receivePin, uint8_t transmitPin, 
                             bool inverse_logic /* = false */);
void mlb_sw_serial_destruct(MlbSwSerial *p);

void mlb_sw_serial_begin(MlbSwSerial *p, long speed);
void mlb_sw_serial_end(MlbSwSerial *p);
bool mlb_sw_serial_listen(MlbSwSerial *p);
bool mlb_sw_serial_is_listening(MlbSwSerial *p);
bool mlb_sw_serial_stop_listening(MlbSwSerial *p);
bool mlb_sw_serial_overflow(MlbSwSerial *p);

/* Use 'mlb_stream' for 'Stream' functionality */
/* Use 'mlb_print' for 'Print' functionality */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SW_SERIAL_H_ */
