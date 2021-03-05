#ifndef MLB_STREAM_H_
#define MLB_STREAM_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

int mlb_stream_available(void *p);
int mlb_stream_read(void *p);
int mlb_stream_peek(void *p);

void mlb_stream_set_timeout(void *p, unsigned long timeout);
unsigned long mlb_stream_get_timeout(void *p);

bool mlb_stream_find(void *p, char *s);
bool mlb_stream_find_n(void *p, char *target, STD_ size_t length);
bool mlb_stream_find_until(void *p, char *target, char *terminator);
bool mlb_stream_find_until_n(void *p, char *target, STD_ size_t targetLen, 
                             char *terminator, STD_ size_t termLen);
STD_ size_t mlb_stream_read_bytes(void *p, char *buffer, STD_ size_t length);
STD_ size_t mlb_stream_read_bytes_until(void *p, char terminator, char *buffer, 
                                        STD_ size_t length);

/* Use 'mlb_print' for 'Print' functionality */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_STREAM_H_ */
