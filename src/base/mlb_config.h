/****************************************************************************************/
/* Global configuration */

#define NDEBUG

#define noMLB_USE_STDLIB_ASSERT
/* If defined, macro 'assert' keeps its definition made in <assert.h>. Otherwise, 'assert'
   gets redefined to 'MLB_ASSERT'. 

   'MLB_USE_STDLIB_ASSERT' does not affect availability of 'MLB_ASSERT' and is supporting 
   declarations. The latter is determined by 'NDEBUG' only */

#define MLB_STRICT_ALIGNMENT_REQUIRED

