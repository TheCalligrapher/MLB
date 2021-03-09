#include "mlb_AdafruitSSD1306.h"
#include "impl/mlb_wrapper.h"

#include <Adafruit_SSD1306.h>

//char a[sizeof(Adafruit_SSD1306)];
//char (*b)[sizeof(MlbAdafruitSSD1306)] = &a;
mlb_static_assert(sizeof(MlbAdafruitSSD1306) == sizeof(Adafruit_SSD1306));

void ada1306_construct_i2c(MlbAdafruitSSD1306 *p, uint8_t w, uint8_t h)
{
  assert(p != nullptr);
  new (p) Adafruit_SSD1306(w, h);
}

void ada1306_construct_sw_spi(MlbAdafruitSSD1306 *p, uint8_t w, uint8_t h, 
                              int8_t mosi_pin, int8_t sclk_pin, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin)
{
  assert(p != nullptr);
  new (p) Adafruit_SSD1306(w, h, mosi_pin, sclk_pin, dc_pin, rst_pin, cs_pin);
}

void ada1306_construct_hw_spi(MlbAdafruitSSD1306 *p, uint8_t w, uint8_t h, void *spi,
                              int8_t dc_pin, int8_t rst_pin, int8_t cs_pin)
{
  assert(p != nullptr);
  new (p) Adafruit_SSD1306(w, h, static_cast<SPIClass *>(spi), dc_pin, rst_pin, cs_pin, 16000000UL);
}

void ada1306_destruct(MlbAdafruitSSD1306 *p)
{
  assert(p != nullptr);
  Adafruit_SSD1306 *d = reinterpret_cast<Adafruit_SSD1306 *>(p);
  d->~Adafruit_SSD1306();
}

void ada1306_begin(MlbAdafruitSSD1306 *p, uint8_t i2caddr)
{
  assert(p != nullptr);
  Adafruit_SSD1306 *d = reinterpret_cast<Adafruit_SSD1306 *>(p);
  d->begin(SSD1306_SWITCHCAPVCC, i2caddr);
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbAdafruitSSD1306
#define MLB_CPP_WRAPPER_CPP_CLASS Adafruit_SSD1306

  MLB_CPP_WRAPPER_DEF(void, ada1306_display, display)
  MLB_CPP_WRAPPER_DEF(void, ada1306_clear_display, clearDisplay)
  MLB_CPP_WRAPPER_DEF(void, ada1306_invert_display, invertDisplay, bool, i)
  MLB_CPP_WRAPPER_DEF(void, ada1306_dim, dim, bool, dim)

  MLB_CPP_WRAPPER_DEF(void, ada1306_start_scroll_right, startscrollright, uint8_t, start, uint8_t, stop)
  MLB_CPP_WRAPPER_DEF(void, ada1306_start_scroll_left, startscrollleft, uint8_t, start, uint8_t, stop)
  MLB_CPP_WRAPPER_DEF(void, ada1306_start_scroll_diag_right, startscrolldiagright, uint8_t, start, uint8_t, stop)
  MLB_CPP_WRAPPER_DEF(void, ada1306_start_scroll_diag_left, startscrolldiagleft, uint8_t, start, uint8_t, stop)
  MLB_CPP_WRAPPER_DEF(void, ada1306_stop_scroll, stopscroll)

  MLB_CPP_WRAPPER_DEF(bool, ada1306_get_pixel, getPixel, int16_t, x, int16_t, y);
  MLB_CPP_WRAPPER_DEF(uint8_t *, ada1306_get_buffer, getBuffer);

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS
