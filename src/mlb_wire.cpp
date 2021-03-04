#include "mlb_wire.h"
#include "impl/mlb_wrapper.h"

#include <Wire.h>

MlbWire *mlb_wire(void)
{
  return (MlbWire *) &Wire;
}

#define MLB_CPP_WRAPPER_GLOBAL Wire

  MLB_CPP_GLOBAL_WRAPPER_DEF(void, mlb_wire_begin, begin)

#undef MLB_CPP_WRAPPER_GLOBAL
