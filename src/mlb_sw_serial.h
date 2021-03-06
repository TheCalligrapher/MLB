#ifndef MLB_SW_SERIAL_H_
#define MLB_SW_SERIAL_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbSwSerial
{
#ifdef ARDUINO_ARCH_AVR
  char fill[31];
#else
  char fill[48];
#endif
} MlbSwSerial;

void mlb_sws_construct(MlbSwSerial *p, uint8_t receivePin, uint8_t transmitPin, 
                       bool inverse_logic /* = false */);
void mlb_sws_destruct(MlbSwSerial *p);

void mlb_sws_begin(MlbSwSerial *p, long speed);
void mlb_sws_end(MlbSwSerial *p);
bool mlb_sws_is_ready(MlbSwSerial *p);

bool mlb_sws_listen(MlbSwSerial *p);
bool mlb_sws_is_listening(MlbSwSerial *p);
bool mlb_sws_stop_listening(MlbSwSerial *p);
bool mlb_sws_overflow(MlbSwSerial *p);

/* Use 'mlb_stream' for 'Stream' functionality */
/* Use 'mlb_print' for 'Print' functionality */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SW_SERIAL_H_ */
