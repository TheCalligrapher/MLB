#ifndef MLB_SSD1306ASCII_H_
#define MLB_SSD1306ASCII_H_

#include "base/mlb_config.h"

#include <stdint.h> /* needed by 'SSD1306init.h' */

typedef struct DevType DevType;
/* To make 'SSD1306init.h' compilable as C code */

#include <SSD1306init.h>
#include <fonts/allFonts.h>

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"
#include "mlb_arduino_co.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

/* Newline will not scroll the display or RAM window. */
#define SCROLL_MODE_OFF  0
/* Newline will scroll both the display and RAM windows. */
#define SCROLL_MODE_AUTO 1
/* Newline scrolls the RAM window. The app scrolls the display window. */
#define SCROLL_MODE_APP  2

void asc1306_set_scroll_mode(void *p, uint8_t mode);
void asc1306_set_font(void *p, const uint8_t* font);
void asc1306_clear(void *p);
void asc1306_clear_to_eol(void *p);
void asc1306_invert_display(void *p, bool invert);
bool asc1306_invert_mode(const void *p);
void asc1306_set_invert_mode(void *p, bool mode);

void asc1306_set_col(void *p, uint8_t col);

/****************************************************************************************/

typedef struct MlbSSD1306AsciiTickerState
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[40];
#else
  char fill[22];
#endif
} MlbSSD1306AsciiTickerState;

void asc1306_ticker_init_ex(void *p, MlbSSD1306AsciiTickerState *pt, 
                            const uint8_t* font, uint8_t row,
                            bool mag2X, uint8_t bgnCol, uint8_t endCol);

void asc1306_ticker_init(void *p, MlbSSD1306AsciiTickerState *pt, 
                         const uint8_t* font, uint8_t row);

bool asc1306_ticker_text_s(void *p, MlbSSD1306AsciiTickerState *pt,  const char *text);

/* CO_FUNCTION(mlb_SSD1306Ascii_ticker_execute, void *p, MlbSSD1306AsciiTickerState *pt); */

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SSD1306ASCII_H_ */
