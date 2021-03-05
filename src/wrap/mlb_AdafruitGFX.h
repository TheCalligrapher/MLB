#ifndef MLB_ADAFRUITGFX_H_
#define MLB_ADAFRUITGFX_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

void agfx_draw_pixel(void *p, int16_t x, int16_t y, uint16_t color);

void agfx_draw_v_line(void *p, int16_t x, int16_t y, int16_t h, uint16_t color);
void agfx_draw_h_line(void *p, int16_t x, int16_t y, int16_t w, uint16_t color);
void agfx_draw_line(void *p, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void agfx_draw_rect(void *p, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void agfx_fill_rect(void *p, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

C_LINKAGE_END

#endif /* MLB_ADAFRUITGFX_H_ */
