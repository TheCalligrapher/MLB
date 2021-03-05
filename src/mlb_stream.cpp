#include "mlb_stream.h"
#include "impl/mlb_wrapper.h"

#define MLB_CPP_WRAPPER_C_STRUCT void
#define MLB_CPP_WRAPPER_CPP_CLASS Stream

  MLB_CPP_WRAPPER_DEF(int, mlb_stream_available, available);
  MLB_CPP_WRAPPER_DEF(int, mlb_stream_read, read);
  MLB_CPP_WRAPPER_DEF(int, mlb_stream_peek, peek);

  MLB_CPP_WRAPPER_DEF(void, mlb_stream_set_timeout, setTimeout, unsigned long, timeout);
  MLB_CPP_WRAPPER_DEF(unsigned long, mlb_stream_get_timeout, getTimeout);

  MLB_CPP_WRAPPER_DEF(bool, mlb_stream_find, find, char *, s);
  MLB_CPP_WRAPPER_DEF(bool, mlb_stream_find_n, find, char *, target, STD_ size_t, length);
  MLB_CPP_WRAPPER_DEF(bool, mlb_stream_find_until, findUntil, char *, target, 
                      char *, terminator);
  MLB_CPP_WRAPPER_DEF(bool, mlb_stream_find_until_n, findUntil, char *, target, 
                      STD_ size_t, targetLen, char *, terminator, STD_ size_t, termLen);
  MLB_CPP_WRAPPER_DEF(STD_ size_t, mlb_stream_read_bytes, readBytes, char *, buffer, 
                      STD_ size_t, length);
  MLB_CPP_WRAPPER_DEF(STD_ size_t, mlb_stream_read_bytes_until, readBytesUntil, 
                      char, terminator, char *, buffer, STD_ size_t, length);

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS
