#include "mlb_stream.h"
#include "impl/mlb_wrapper.h"

#define MLB_CPP_WRAPPER_C_STRUCT void
#define MLB_CPP_WRAPPER_CPP_CLASS Stream

  MLB_CPP_WRAPPER_DEF(int, mlb_stream_available, available);
  MLB_CPP_WRAPPER_DEF(int, mlb_stream_read, read);
  MLB_CPP_WRAPPER_DEF(int, mlb_stream_peek, peek);

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS
