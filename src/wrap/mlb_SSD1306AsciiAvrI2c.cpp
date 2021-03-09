#ifndef ARDUINO_ARCH_SAMD

#include "mlb_SSD1306AsciiAvrI2c.h"
#include "impl/mlb_wrapper.h"

#include <SSD1306AsciiAvrI2c.h>

//char a[sizeof(SSD1306AsciiAvrI2c)];
//char (*b)[sizeof(MlbSSD1306AsciiAvrI2c)] = &a;
mlb_static_assert(sizeof(MlbSSD1306AsciiAvrI2c) == sizeof(SSD1306AsciiAvrI2c));

void asc1306_avri2c_construct(MlbSSD1306AsciiAvrI2c *p)
{
  assert(p != nullptr);
  new (p) SSD1306AsciiAvrI2c;
}

void asc1306_avri2c_destruct(MlbSSD1306AsciiAvrI2c *p)
{
  assert(p != nullptr);
  SSD1306AsciiAvrI2c *d = reinterpret_cast<SSD1306AsciiAvrI2c *>(p);
  d->~SSD1306AsciiAvrI2c();
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbSSD1306AsciiAvrI2c
#define MLB_CPP_WRAPPER_CPP_CLASS SSD1306AsciiAvrI2c

  MLB_CPP_WRAPPER_DEF(void, asc1306_avri2c_begin, begin, const DevType *, dev, uint8_t, i2cAddr)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

#endif /* architectures */