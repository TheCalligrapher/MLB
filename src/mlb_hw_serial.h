#ifndef MLB_HW_SERIAL_H_
#define MLB_HW_SERIAL_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbHwSerial MlbHwSerial;

MlbHwSerial *mlb_serial1(void);
MlbHwSerial *mlb_serial2(void);
MlbHwSerial *mlb_serial3(void);
MlbHwSerial *mlb_serial4(void);

void mlb_hw_serial_begin(MlbHwSerial *serial, unsigned long baud);

/* Use 'mlb_print' for 'Print' functionality */
/* Use 'mlb_stream' for 'Stream' functionality */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_HW_SERIAL_H_ */
