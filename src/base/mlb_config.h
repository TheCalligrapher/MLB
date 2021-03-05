/****************************************************************************************/
/* Global configuration */

#define NDEBUG

#ifndef MLB_USE_STDLIB_ASSERT
  #define MLB_USE_STDLIB_ASSERT 0
#endif
/* If defined, macro 'assert' keeps its definition made in <assert.h>. Otherwise, 'assert'
   gets redefined to 'MLB_ASSERT'. 

   'MLB_USE_STDLIB_ASSERT' does not affect availability of 'MLB_ASSERT' and is supporting 
   declarations. The latter is determined by 'NDEBUG' only */

#ifndef MLB_STRICT_ALIGNMENT_REQUIRED
  #define MLB_STRICT_ALIGNMENT_REQUIRED 1
#endif

