#include "mlb_SSD1306Ascii.h"
#include "impl/mlb_wrapper.h"

#include <SSD1306Ascii.h>

//char a[sizeof(TickerState)];
//char (*b)[sizeof(MlbSSD1306AsciiTickerState)] = &a;
mlb_static_assert(sizeof(MlbSSD1306AsciiTickerState) == sizeof(TickerState));

#define MLB_CPP_WRAPPER_C_STRUCT void
#define MLB_CPP_WRAPPER_CPP_CLASS SSD1306Ascii

  MLB_CPP_WRAPPER_DEF(void, asc1306_set_scroll_mode, setScrollMode, uint8_t, mode)
  MLB_CPP_WRAPPER_DEF(void, asc1306_set_font, setFont, const uint8_t*, font)
  MLB_CPP_WRAPPER_DEF(void, asc1306_clear, clear)
  MLB_CPP_WRAPPER_DEF(void, asc1306_clear_to_eol, clearToEOL)
  MLB_CPP_WRAPPER_DEF(void, asc1306_invert_display, invertDisplay, bool, invert)
  MLB_CPP_WRAPPER_CONST_DEF(bool, asc1306_invert_mode, invertMode)
  MLB_CPP_WRAPPER_DEF(void, asc1306_set_invert_mode, setInvertMode, bool, mode)

  MLB_CPP_WRAPPER_DEF(void, asc1306_set_col, setCol, uint8_t, col)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

/****************************************************************************************/

void asc1306_ticker_init_ex(void *p, MlbSSD1306AsciiTickerState *pt, 
                            const uint8_t* font, uint8_t row,
                            bool mag2X /* = false */, 
                            uint8_t bgnCol /* = 0 */, uint8_t endCol /* = 255 */)
{
  assert(p != nullptr && pt != nullptr);
  SSD1306Ascii *d = reinterpret_cast<SSD1306Ascii *>(p);
  TickerState *t = reinterpret_cast<TickerState *>(pt);
  d->tickerInit(t, font, row, mag2X, bgnCol, endCol);
}

void asc1306_ticker_init(void *p, MlbSSD1306AsciiTickerState *pt, 
                         const uint8_t* font, uint8_t row)
{
  asc1306_ticker_init_ex(p, pt, font, row, false, 0, 255);
}

bool asc1306_ticker_text_s(void *p, MlbSSD1306AsciiTickerState *pt, const char *text)
{
  assert(p != nullptr && pt != nullptr);
  SSD1306Ascii *d = reinterpret_cast<SSD1306Ascii *>(p);
  TickerState *t = reinterpret_cast<TickerState *>(pt);
  return d->tickerText(t, text);
}

static inline int8_t asc1306_ticker_tick(void *p, MlbSSD1306AsciiTickerState *pt)
{
  assert(p != nullptr && pt != nullptr);
  SSD1306Ascii *d = reinterpret_cast<SSD1306Ascii *>(p);
  TickerState *t = reinterpret_cast<TickerState *>(pt);
  return d->tickerTick(t);
}

/*
CO_FUNCTION_DEFINE(mlb_SSD1306Ascii_ticker_execute, 
                   void *p, MlbSSD1306AsciiTickerState *pt)
{
  CO_BEGIN

  for (;;)
  {
    asc1306_ticker_tick(COP.p, COP.pt);
    CO_INVOKE(co_delay, 50);
  }

  CO_END
}
*/