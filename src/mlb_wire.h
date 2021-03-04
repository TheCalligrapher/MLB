#ifndef MLB_WIRE_H_
#define MLB_WIRE_H_

#include "base/mlb_config.h"

#include "mlb_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbWire MlbWire;

MlbWire *mlb_wire(void);

void mlb_wire_begin(void);

/* Use 'mlb_print' for 'Print' functionality */
/* Use 'mlb_stream' for 'Stream' functionality */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_WIRE_H_ */
