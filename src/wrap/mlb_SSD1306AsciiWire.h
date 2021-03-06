#ifndef MLB_SSD1306ASCIIWIRE_H_
#define MLB_SSD1306ASCIIWIRE_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

#include "wrap/mlb_SSD1306Ascii.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbSSD1306AsciiWire
{
#ifdef ARDUINO_ARCH_AVR
  char fill[20];
#else
  char fill[36];
#endif
} MlbSSD1306AsciiWire;

void asc1306_wire_construct(MlbSSD1306AsciiWire *p);
void asc1306_wire_destruct(MlbSSD1306AsciiWire *p);
void asc1306_wire_begin(MlbSSD1306AsciiWire *p, const DevType *dev, uint8_t i2cAddr);

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SSD1306ASCIIWIRE_H_ */
