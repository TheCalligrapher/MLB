#ifndef MLB_STREAM_H_
#define MLB_STREAM_H_

#include "base/mlb_config.h"

#include "mlb_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

int mlb_stream_available(void *p);
int mlb_stream_read(void *p);
int mlb_stream_peek(void *p);

/* Use 'mlb_print' for 'Print' functionality */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_STREAM_H_ */
