#include "mlb_SSD1306AsciiWire.h"
#include "impl/mlb_wrapper.h"

#include <SSD1306AsciiWire.h>

//char a[sizeof(SSD1306AsciiWire)];
//char (*b)[sizeof(MlbSSD1306AsciiWire)] = &a;
mlb_static_assert(sizeof(MlbSSD1306AsciiWire) == sizeof(SSD1306AsciiWire));

void asc1306_wire_construct(MlbSSD1306AsciiWire *p)
{
  assert(p != nullptr);
  new (p) SSD1306AsciiWire;
}

void asc1306_wire_destruct(MlbSSD1306AsciiWire *p)
{
  assert(p != nullptr);
  SSD1306AsciiWire *d = reinterpret_cast<SSD1306AsciiWire *>(p);
  d->~SSD1306AsciiWire();
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbSSD1306AsciiWire
#define MLB_CPP_WRAPPER_CPP_CLASS SSD1306AsciiWire

  MLB_CPP_WRAPPER_DEF(void, asc1306_wire_begin, begin, const DevType *, dev, uint8_t, i2cAddr)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS
