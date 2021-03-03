#include "mlb_wire.h"
#include "impl/mlb_wrapper.h"

#include <Wire.h>

void *mlb_wire(void)
{
  return &Wire;
}

#define MLB_CPP_WRAPPER_GLOBAL Wire

  MLB_CPP_GLOBAL_WRAPPER_DEF(void, mlb_wire_begin, begin)

#undef MLB_CPP_WRAPPER_GLOBAL
