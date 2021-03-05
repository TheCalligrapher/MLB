#ifndef MLB_CO_H_
#define MLB_CO_H_

#include "mlb_co_config.h"

#include "../base/mlb_pp.h"
#include "../base/mlb_common.h"
#include "../base/mlb_assert.h"

/****************************************************************************************/

#if CO_TRACK_STACK_USAGE
  #define CO_SUSG_ONLY(x_) x_
  #define CO_SUSG_ARG(x_) x_,
#else /* CO_TRACK_STACK_USAGE */
  #define CO_SUSG_ONLY(x_) 
  #define CO_SUSG_ARG(x_)
#endif /* CO_TRACK_STACK_USAGE */

#if CO_TRACK_STACK_USAGE || !defined(NDEBUG)
  #define CO_DBG_SUSG_ONLY(x_) x_
  #define CO_DBG_SUSG_ARG(x_) x_,
#else /* CO_TRACK_STACK_USAGE || !NDEBUG */
  #define CO_DBG_SUSG_ONLY(x_) 
  #define CO_DBG_SUSG_ARG(x_)
#endif /* CO_TRACK_STACK_USAGE || !NDEBUG */

#if CO_REPORT_STACK_SIZE
  #define CO_REPORT_SSIZE_ONLY(x_) x_
#else /* CO_REPORT_STACK_SIZE */
  #define CO_REPORT_SSIZE_ONLY(x_)
#endif /* CO_REPORT_STACK_SIZE */

/****************************************************************************************/

#define CO_PP_ASEMI__(a_) a_;
#define CO_PP_SEMIS(...) MLB_APPLY_1(CO_PP_ASEMI__, ##__VA_ARGS__)

/****************************************************************************************/

typedef unsigned char CoByte;

#define CO_ADD_BYTES__(p, d) ((CoByte *) (p) + (d))

/****************************************************************************************/

#if CO_ENABLE_ROOT_CONTEXT

  #define CO_RCON_ONLY(x_) x_
  #define CO_RCON_ARG(x_) x_,

  #define CO_ROOT_SUSG MLB_STRICT_ALIGN_UP(sizeof(CoRootContext), MLB_STRICT_ALIGN_MAX)
  #define CORC (*corc__)

#else /* CO_ENABLE_ROOT_CONTEXT */

  #define CO_RCON_ONLY(x_) 
  #define CO_RCON_ARG(x_)

  #define CO_ROOT_SUSG 0u

#endif /* CO_ENABLE_ROOT_CONTEXT */

/****************************************************************************************/

#if CO_TRACK_STACK_USAGE || !defined(NDEBUG)

struct CoRootDbgContext__
{
  unsigned co_id__;
  CoByte *co_stack_bottom__;
  STD_ size_t co_stack_size__;
  STD_ size_t co_stack_usage__;
};

/* These fields are grouped into a separate struct and passed to co-functions though 
   a separate parameter (as opposed to being declared inside 'CoRootContext') because 
   we don't want 'CO_TRACK_STACK_USAGE' mode to affect the stack usage. (Note that 
   'CoRootContext' has to be allocated inside co-thread's stack.) This 
   'CoRootDbgContext__' can be allocated on per-call-site basis, as a 'static' object, 
   thus eliminating its impact on co-thread's stack usage */

#define CODRC (*codrc__)

#define CO_IN_STACK__(p)\
  (((CoByte *) p) >= CODRC.co_stack_bottom__ &&\
   ((CoByte *) p) <= CODRC.co_stack_bottom__ + CODRC.co_stack_size__)

#define CO_STACK_USAGE__() ((STD_ size_t) (co_brk__ - CODRC.co_stack_bottom__))

#endif /* CO_TRACK_STACK_USAGE || !NDEBUG */

#if CO_TRACK_STACK_USAGE

  #define CO_UPDATE_SUSG__()\
    (CODRC.co_stack_usage__ = MLB_MAX(CODRC.co_stack_usage__, CO_STACK_USAGE__()))
  /* Invoke afert each increase of 'co_brk__' */

  extern void (*g_co_susg_reporter)(unsigned id, STD_ size_t usage);

  static inline void co_report_susg__(unsigned id, STD_ size_t usage)
  {
    if (g_co_susg_reporter != NULL)
      g_co_susg_reporter(id, usage);
  }

#endif /* CO_TRACK_STACK_USAGE */

#if CO_REPORT_STACK_SIZE

  extern void (*g_co_ssize_reporter)(unsigned id, STD_ size_t size);

  static inline void co_report_ssize__(unsigned id, STD_ size_t size)
  {
    if (g_co_ssize_reporter != NULL)
      g_co_ssize_reporter(id, size);
  }

#endif /* CO_REPORT_STACK_SIZE */

/****************************************************************************************/
/* Jump method */

#if CO_USE_RUNTIME_GOTO

  typedef void *CoState__;

  #define CO_LABEL__(i_) MLB_PP_CONCAT(MLB_PP_CONCAT(MLB_PP_CONCAT(co_lbl__, __LINE__), _), i_)
  #define CO_STATE__(i_) &&CO_LABEL__(i_)

  #define CO_STATE_DISPATCHER_BEGIN__ if (COP.co_state__ != 0) goto *COP.co_state__;
  #define CO_STATE_DISPATCHER_END__ COP.co_state__ = 0;

#else /* CO_USE_RUNTIME_GOTO */

  typedef STD_ size_t CoState__;

  #define CO_MAX_LINES__ 1024u
  /* Assumes that no co-function is longer than 'CO_MAX_LINES' lines, i.e. 
     '__LINE__ % CO_MAX_LINES' produces a unique label within a given function */

  #define CO_LINE_ID__(i_) (1u + (i_) * CO_MAX_LINES__ + __LINE__ % CO_MAX_LINES__)

  #define CO_LABEL__(i_) case CO_LINE_ID__(i_)
  #define CO_STATE__(i_) CO_LINE_ID__(i_)

  #define CO_STATE_DISPATCHER_BEGIN__ switch (COP.co_state__) { case 0:
  #define CO_STATE_DISPATCHER_END__ } COP.co_state__ = 0;
  /* It is important to set 'co_state__' to zero once the function is completed (i.e. at 
     "full" exit, not at yield). This is to ensure that the caller knows the function is 
     finished (see 'CO_INVOKE', for example) */

#endif /* CO_USE_RUNTIME_GOTO */

/****************************************************************************************/
/* Parametrs */

#define COP_TYPE__(f_) struct MLB_PP_CONCAT(CoParams__, f_)

#define COP_BEGIN__(f_) COP_TYPE__(f_) { CoState__ co_state__;
/* 'co_state__' field is a part of parameters struct, not of locals struct. This is done 
   that way to make its location predictable to the caller, since caller sometimes has to 
   access callee's 'co_state__' */

#define COP_END__ };

#define COP_SUSG(f_) sizeof(COP_TYPE__(f_))

#define COP (*cop__)

/****************************************************************************************/
/* Locals */

#define COL_TYPE__(f_) struct MLB_PP_CONCAT(CoLocals__, f_)

#define COL_BEGIN_STATIC__(f_) COL_TYPE__(f_) { struct
#define COL_BEGIN_DYNAMIC__(f_) COL_TYPE__(f_) { CoByte *co_persistent_brk__; struct
/* Functions that support 'CO_ALLOCA' need a persistent pointer to the current top of the 
   stack. Functions that do not support 'CO_ALLOCA' can get by with a local non-persistent 
   (calculated) pointer to the current top of the stack 
   
   A nested anonymous truct is intended to facilitate enclosing locals into '{}' braces 
   for purely cosmetic reasons */

#define COL_END__ ;};

#define COL_SUSG(f_) sizeof(COL_TYPE__(f_))

#define COL (*col__)

/****************************************************************************************/
/* Function declaration 

    CO_PROTOTYPE(foo, params)
    {
      locals
    }
    CO_PROTOTYPE_END
*/

#define CO_PROTOTYPE__(f_)\
  void f_(CO_RCON_ARG(CoRootContext *const corc__)\
          CO_DBG_SUSG_ARG(struct CoRootDbgContext__ *const codrc__)\
          COP_TYPE__(f_) *const cop__)

#define CO_PROTOTYPE(f_, ...)\
  COP_BEGIN__(f_) CO_PP_SEMIS(__VA_ARGS__) COP_END__\
  CO_PROTOTYPE__(f_);\
  COL_BEGIN_STATIC__(f_)

#define CO_PROTOTYPE_DYNAMIC(f_, ...)\
  COP_BEGIN__(f_) CO_PP_SEMIS(__VA_ARGS__) COP_END__\
  CO_PROTOTYPE__(f_);\
  COL_BEGIN_DYNAMIC__(f_)

#define CO_PROTOTYPE_END COL_END__

#ifndef _MSC_VER
  #define CO_PROTOTYPE_NO_LOCALS(f_, ...)\
    CO_PROTOTYPE(f_, ##__VA_ARGS__) {} CO_PROTOTYPE_END
#else
  #define CO_PROTOTYPE_NO_LOCALS(f_, ...)\
    CO_PROTOTYPE(f_, ##__VA_ARGS__) { char dummy__; } CO_PROTOTYPE_END
#endif

#define COF_SUSG(f_) (COP_SUSG(f_) + COL_SUSG(f_))
#define COF_ROOT_SUSG(f_) (CO_ROOT_SUSG + COF_SUSG(f_))
/* Static stack usage of a co-function */

#define COF_1_PLUS_SUSG__(a_) + COF_SUSG(a_)
#define COF_SUSGS(...) MLB_APPLY_FM_1(COL_SUSG, COF_1_PLUS_SUSG__, ##__VA_ARGS__)
#define COF_ROOT_SUSGS(...) (CO_ROOT_SUSG + COF_SUSGS(__VA_ARGS__))

/****************************************************************************************/
/* Function stratup */

/* Bootstrap is performed every time the function is entered, regardless of whether this 
   is the initial call or a context switch. Bootstrap restores calculated local values */

#define CO_BOOTSTRAP_FRAME_STATIC__()\
  CoLocals__ *const col__ = (CoLocals__ *) CO_ADD_BYTES__(cop__, sizeof *cop__);\
  CoByte *const co_brk__ = CO_ADD_BYTES__(col__, sizeof *col__);\
  assert(CO_IN_STACK__(co_brk__));
/* 'co_brk__' is constant */

#define CO_BOOTSTRAP_FRAME_DYNAMIC__()\
  CoLocals__ *const col__ = (CoLocals__ *) CO_ADD_BYTES__(cop__, sizeof *cop__);\
  CoByte *co_brk__ = COL.co_persistent_brk__;
/* On initial call 'co_brk__' will end up with a meaningless value from 
   'COL.co_persistent_brk__'. 'CO_SETUP_FRAME_DYNAMIC__' will set both to a valid 
   value. 'co_brk__' is not constant */

/* Initial setup is performed only when the function is called initially (not a return 
   from context switch). It initializes persistent values */

#define CO_SETUP_FRAME_STATIC__()\
  CO_SUSG_ONLY(CO_UPDATE_SUSG__());

#define CO_SETUP_FRAME_DYNAMIC__()\
  co_brk__ = CO_ADD_BYTES__(col__, sizeof *col__);\
  assert(CO_IN_STACK__(co_brk__));\
  COL.co_persistent_brk__ = co_brk__;\
  CO_SUSG_ONLY(CO_UPDATE_SUSG__());

/****************************************************************************************/
/* Function definition that follows a prototype

    CO_FUNCTION_DEFINITION(foo)
    {
      CO_BEGIN or CO_BEGIN_DYNAMIC

      code

      CO_END
    }
*/

#define CO_FUNCTION_DEFINITION(f_) CO_PROTOTYPE__(f_) {\
  typedef COL_TYPE__(f_) CoLocals__;\

#define CO_BEGIN\
  CO_BOOTSTRAP_FRAME_STATIC__();\
  CO_STATE_DISPATCHER_BEGIN__;\
  CO_SETUP_FRAME_STATIC__();

#define CO_BEGIN_DYNAMIC\
  CO_BOOTSTRAP_FRAME_DYNAMIC__();\
  CO_STATE_DISPATCHER_BEGIN__;\
  CO_SETUP_FRAME_DYNAMIC__();

#define CO_END CO_STATE_DISPATCHER_END__; }
/* This closing brace will actually end up being a match for the user-provided opening 
   brace after 'CO_FUNCTION_DEFINITION'. Meanwhile, the user-provided closing brace at the 
   end of function body will match the opening brace inside 'CO_FUNCTION_DEFINITION' */

#define CO_YIELD__(i_) do {\
    COP.co_state__ = CO_STATE__(i_); return; CO_LABEL__(i_):;\
  } while (0)

#define CO_YIELD() CO_YIELD__(0)
#define CO_RETURN() do { COP.co_state__ = 0; return; } while (0)

/****************************************************************************************/
/* Standalone function definition 

    CO_PROTOTYPE(foo, params)
    {
      locals
    }
    CO_BODY(foo)
    {
      CO_BEGIN or CO_BEGIN_DYNAMIC

      code

      CO_END
    }

   or 

    CO_FUNCTION_NO_LOCALS(foo, params)
    {
      CO_BEGIN

      code

      CO_END
    }
*/

#define CO_BODY(f_) CO_PROTOTYPE_END CO_FUNCTION_DEFINITION(f_)

#define CO_FUNCTION_NO_LOCALS(f_, ...)\
  CO_PROTOTYPE_NO_LOCALS(f_, ##__VA_ARGS__) CO_FUNCTION_DEFINITION(f_)

/****************************************************************************************/

#define CO_ALLOCA(size_, align_)\
  (assert(COL.co_persistent_brk__ == co_brk__),\
   COL.co_persistent_brk__ = co_brk__ = MLB_STRICT_ALIGN_UP_PTR(co_brk__, align_),\
   COL.co_persistent_brk__ = (co_brk__ += (size_)),\
   assert(CO_IN_STACK__(co_brk__)),\
   CO_SUSG_ARG(CO_UPDATE_SUSG__())\
   (void *) (co_brk__ - (size_)))

#define CO_ZALLOCA(size_, align_) memset(CO_ALLOCA(size_, align_), 0, size_)

#define CO_ALLOCA_T(T_, count_) CO_ALLOCA((STD_ size_t) count_ * sizeof(T_), alignof(T_))  
#define CO_ZALLOCA_T(T_, count_) CO_ZALLOCA((STD_ size_t) count_ * sizeof(T_), alignof(T_))

/****************************************************************************************/

#define COP_NEXT__(f_) (*(COP_TYPE__(f_) *) co_brk__)

/* Invoke a co-function from another co-function */
#define CO_INVOKE(f_, ...) do {\
    assert(CO_IN_STACK__(CO_ADD_BYTES__(&COP_NEXT__(f_), sizeof COP_NEXT__(f_))));\
    COP_NEXT__(f_) = MLB_INITIALIZER(COP_TYPE__(f_), 0, ##__VA_ARGS__ );\
    while (f_(CO_RCON_ARG(corc__) CO_DBG_SUSG_ARG(codrc__) &COP_NEXT__(f_)),\
           COP_NEXT__(f_).co_state__ != 0)\
      CO_YIELD();\
  } while (0)

/****************************************************************************************/

#define CO_ROOT_INVOKE__(id_, stack_, stack_size_, f_, ...) do {\
    assert((id_) != 0);\
    \
    CO_REPORT_SSIZE_ONLY(\
      static bool s_co_ssize_reported__;\
      if (!s_co_ssize_reported__) {\
        co_report_ssize__((id_), (stack_size_));\
        s_co_ssize_reported__ = true;\
      }\
    )\
    \
    CO_DBG_SUSG_ONLY(\
      static struct CoRootDbgContext__ s_codrc__;\
      if (s_codrc__.co_id__ == 0)\
        s_codrc__ = MLB_INITIALIZER(struct CoRootDbgContext__ MLB_PP_COMMA\
          (id_) MLB_PP_COMMA\
          (stack_) MLB_PP_COMMA\
          (stack_size_));\
      struct CoRootDbgContext__ *const codrc__ = &s_codrc__;\
    )\
    \
    CoByte *co_brk__ = (CoByte *) (stack_);\
    \
    CO_RCON_ONLY(\
      CoRootContext *corc__ = (CoRootContext *) co_brk__;\
      co_brk__ += sizeof *corc__;\
      assert(CO_IN_STACK__(co_brk__));\
    )\
    \
    assert(CO_IN_STACK__(co_brk__ + sizeof COP_NEXT__(f_)));\
    if (COP_NEXT__(f_).co_state__ == 0) {\
      CO_RCON_ONLY(co_init_root_context(corc__));\
      COP_NEXT__(f_) = MLB_INITIALIZER(COP_TYPE__(f_), 0, __VA_ARGS__);\
    }\
    \
    CO_RCON_ONLY(\
      if (!co_process_root_context(corc__))\
        break;\
    )\
    \
    f_(CO_RCON_ARG(corc__) CO_DBG_SUSG_ARG(codrc__) &COP_NEXT__(f_));\
    \
    CO_SUSG_ONLY(\
      static STD_ size_t s_co_max_stack_usage__;\
      if (codrc__->co_stack_usage__ > s_co_max_stack_usage__) {\
        s_co_max_stack_usage__ = codrc__->co_stack_usage__;\
        co_report_susg__(codrc__->co_id__, s_co_max_stack_usage__);\
      }\
    );\
  } while (0)

/****************************************************************************************/
/* Invocation in an externally imposed cycle (Arduino's 'loop()' function etc.)
   Repetitive invocation: once/if coroutine is completed it is invoked again from scratch */

#define CO_ROOT_INVOKE_SSIZE_L(id_, stack_size_, f_, ...) do {\
    static alignas(MLB_STRICT_ALIGN_MAX) CoByte co_stack__[stack_size_];\
    CO_ROOT_INVOKE__(id_, co_stack__, stack_size_, f_, ##__VA_ARGS__);\
  } while (0)

#define CO_ROOT_INVOKE_L(id, f_, ...)\
  CO_ROOT_INVOKE_SSIZE_L(id, COF_ROOT_SUSG(f_), f_, ##__VA_ARGS__)

/****************************************************************************************/

#define CO_SUB_ROOT_SSIZE_INVOKE(id_, sub_stack_, sub_stack_size_, f_, ...)\
  CO_ROOT_INVOKE__(id_, sub_stack_, sub_stack_size_, f_, ##__VA_ARGS__)

/****************************************************************************************/
/* Invocation in a normal program flow: invoked between 'CO_ROOT_BEGIN' and 'CO_ROOT_END', 
   waits till all co-threads complete (i.e. "join"), then continues execution after 
   'CO_ROOT_END' */

#define CO_ROOT_SSIZE_INVOKE(id_, stack_size_, f_, ...) do {\
    static alignas(MLB_STRICT_ALIGN_MAX) CoByte co_stack__[stack_size_];\
    if (COP_FIRST__(co_stack__, f_).co_state__ == 0) ++co_entries__;\
    CO_ROOT_INVOKE__(id_, co_stack__, stack_size_, f_, __VA_ARGS__);\
    if (COP_FIRST__(co_stack__, f_).co_state__ == 0) --co_entries__;\
  } while (0)

#define CO_ROOT_INVOKE(id_, f_, ...)\
  CO_ROOT_SSIZE_INVOKE(id, COF_ROOT_SUSG(f_), f_, ##__VA_ARGS__)

#define CO_ROOT_BEGIN do { unsigned co_entries__ = 0; do {
#define CO_ROOT_END } while (co_entries__ > 0); } while (0);

#endif /* MLB_CO_H_ */
