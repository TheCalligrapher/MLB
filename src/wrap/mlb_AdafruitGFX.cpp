#include "mlb_AdafruitGFX.h"
#include "impl/mlb_wrapper.h"

#include <new>
#include <Adafruit_GFX.h>

#define MLB_CPP_WRAPPER_C_STRUCT void
#define MLB_CPP_WRAPPER_CPP_CLASS Adafruit_GFX

  MLB_CPP_WRAPPER_DEF(void, agfx_draw_pixel, drawPixel, int16_t, x, int16_t, y, uint16_t, color)

  MLB_CPP_WRAPPER_DEF(void, agfx_draw_v_line, drawFastVLine, int16_t, x, int16_t, y, int16_t, h, uint16_t, color)
  MLB_CPP_WRAPPER_DEF(void, agfx_draw_h_line, drawFastHLine, int16_t, x, int16_t, y, int16_t, w, uint16_t, color)
  MLB_CPP_WRAPPER_DEF(void, agfx_draw_line, drawLine, int16_t, x0, int16_t, y0, int16_t, x1, int16_t, y1, uint16_t, color)

  MLB_CPP_WRAPPER_DEF(void, agfx_draw_rect, drawRect, int16_t, x, int16_t, y, int16_t, w, int16_t, h, uint16_t, color)
  MLB_CPP_WRAPPER_DEF(void, agfx_fill_rect, fillRect, int16_t, x, int16_t, y, int16_t, w, int16_t, h, uint16_t, color)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS
