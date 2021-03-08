/****************************************************************************************/
/* Global configuration */

#ifndef MLB_DEBUG
  #define MLB_DEBUG 0
#endif /* MLB_DEBUG */

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
/* When set to '0', no effort is made to align data. When set to '1' the data is aligned 
   by its natural alignment requirements. The latter could still be "unaligned" though, 
   depending on the platform */

/****************************************************************************************/

#if MLB_DEBUG
  #undef NDEBUG
#else
  #ifndef NDEBUG
    #define NDEBUG
  #endif
#endif

#if defined(__GNUC__) && defined(__AVR_ARCH__)
  #define MLB_USE_CPP_STD 0
#else
  #define MLB_USE_CPP_STD 1
#endif

#ifdef _MSC_VER
  #pragma warning(disable: 5105)
#endif

