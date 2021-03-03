#ifndef MLB_ADAFRUITSSD1306_H_
#define MLB_ADAFRUITSSD1306_H_

#include "base/mlb_config.h"
#include "mlb_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

#define SSD1306_BLACK    0
#define SSD1306_WHITE    1
#define SSD1306_INVERSE  2

typedef struct MlbAdafruitSSD1306
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[108];
#else
  char fill[64];
#endif
} MlbAdafruitSSD1306;

void ada1306_construct_i2c(MlbAdafruitSSD1306 *p, uint8_t w, uint8_t h);
void ada1306_construct_sw_spi(MlbAdafruitSSD1306 *p, uint8_t w, uint8_t h, 
                              int8_t mosi_pin, int8_t sclk_pin, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin);
void ada1306_construct_hw_spi(MlbAdafruitSSD1306 *p, uint8_t w, uint8_t h, void *spi,
                              int8_t dc_pin, int8_t rst_pin, int8_t cs_pin);
void ada1306_destruct(MlbAdafruitSSD1306 *p);

void ada1306_begin(MlbAdafruitSSD1306 *p, uint8_t i2caddr);

void ada1306_clear_display(MlbAdafruitSSD1306 *p);
void ada1306_invert_display(MlbAdafruitSSD1306 *p, uint8_t i);
void ada1306_display(MlbAdafruitSSD1306 *p);
 
void ada1306_start_scroll_right(MlbAdafruitSSD1306 *p, uint8_t start, uint8_t stop);
void ada1306_start_scroll_left(MlbAdafruitSSD1306 *p, uint8_t start, uint8_t stop);
void ada1306_start_scroll_diag_right(MlbAdafruitSSD1306 *p, uint8_t start, uint8_t stop);
void ada1306_start_scroll_diag_left(MlbAdafruitSSD1306 *p, uint8_t start, uint8_t stop);
void ada1306_stop_scroll(MlbAdafruitSSD1306 *p);

void ada1306_dim(MlbAdafruitSSD1306 *p, bool dim);

bool ada1306_get_pixel(MlbAdafruitSSD1306 *p, int16_t x, int16_t y);
uint8_t *ada1306_get_buffer(MlbAdafruitSSD1306 *p);

C_LINKAGE_END

#endif /* MLB_ADAFRUITSSD1306_H_ */
