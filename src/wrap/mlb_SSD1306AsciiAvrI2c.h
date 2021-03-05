#ifndef MLB_SSD1306ASCIIAVRI2C_H_
#define MLB_SSD1306ASCIIAVRI2C_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

#include "wrap/mlb_SSD1306Ascii.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbSSD1306AsciiAvrI2c
{
  char fill[21];
} MlbSSD1306AsciiAvrI2c;

void asc1306_avri2c_construct(MlbSSD1306AsciiAvrI2c *p);
void asc1306_avri2c_destruct(MlbSSD1306AsciiAvrI2c *p);
void asc1306_avri2c_begin(MlbSSD1306AsciiAvrI2c *p, const DevType *dev, uint8_t i2cAddr);

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SSD1306ASCIIAVRI2C_H_ */
