#include "mlb_assert.h"

#ifndef NDEBUG

void (*g_mlb_assert_handler)(const char *, const char *, int);

void mlb_assert(const char *arg, const char *file, int line)
{
  if (g_mlb_assert_handler != NULL)
    g_mlb_assert_handler(arg, file, line);
  abort();
}

#endif  /* NDEBUG */
