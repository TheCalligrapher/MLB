#include "mlb_spi.h"
#include "impl/mlb_wrapper.h"

#include <SPI.h>

MlbSpi *mlb_spi(void)
{
  return (MlbSpi *) &SPI;
}

#define MLB_CPP_WRAPPER_GLOBAL SPI

  MLB_CPP_GLOBAL_WRAPPER_DEF(void, mlb_spi_begin, begin)

#undef MLB_CPP_WRAPPER_GLOBAL
