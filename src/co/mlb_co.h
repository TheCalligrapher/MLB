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
#define CO_PP_SEMIS(...) MLB_PP_APPLY_U(CO_PP_ASEMI__, ##__VA_ARGS__)

/****************************************************************************************/

#define CO_STACK_ALIGN MLB_STRICT_ALIGN_MAX

typedef unsigned char CoByte;

/****************************************************************************************/

#if CO_ENABLE_ROOT_CONTEXT

  #define CO_RCON_ONLY(x_) x_
  #define CO_RCON_ARG(x_) x_,

  #define CO_ROOT_SUSG sizeof(CoRootContext)
  #define CORC (*corc__)

#else /* CO_ENABLE_ROOT_CONTEXT */

  #define CO_RCON_ONLY(x_) 
  #define CO_RCON_ARG(x_)

  #define CO_ROOT_SUSG 0u

#endif /* CO_ENABLE_ROOT_CONTEXT */

/****************************************************************************************/

#if CO_TRACK_STACK_USAGE || !defined(NDEBUG)

struct CoDbgRootContext__
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
   'CoDbgRootContext__' can be allocated on per-call-site basis, as a 'static' object, 
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
/* Dispatching method */

/* It is important to set 'col__->cop__.co_state__' to zero once the function is completed 
   (i.e. at "full" exit, not at yield). This is to ensure that the caller knows the 
   function is finished (see 'CO_INVOKE', for example) */

#if CO_USE_RUNTIME_GOTO

  typedef void *CoState__;

  #define CO_STATE_NEW__    0
  #define CO_STATE_JOINED__ ((CoState__) (STD_ uintptr_t) -1)

  #define CO_LABEL__(i_) MLB_PP_CONCAT(MLB_PP_CONCAT(MLB_PP_CONCAT(co_lbl__, __LINE__), _), i_)
  #define CO_STATE__(i_) &&CO_LABEL__(i_)

  #define CO_STATE_DISPATCHER_BEGIN__\
    assert(col__->cop__.co_state__ != CO_STATE_JOINED__);\
    if (col__->cop__.co_state__ != CO_STATE_NEW__) goto *col__->cop__.co_state__;

  #define CO_STATE_DISPATCHER_END__ col__->cop__.co_state__ = CO_STATE_JOINED__;

#else /* CO_USE_RUNTIME_GOTO */

  typedef STD_ size_t CoState__;

  #define CO_STATE_NEW__    0
  #define CO_STATE_JOINED__ ((STD_ size_t) -1)

  #define CO_MAX_LINES__ 1024u
  /* Assumes that no co-function is longer than 'CO_MAX_LINES' lines, i.e. 
     '__LINE__ % CO_MAX_LINES' produces a unique label within a given function */

  #define CO_LINE_ID__(i_) (1u + (i_) * CO_MAX_LINES__ + __LINE__ % CO_MAX_LINES__)

  #define CO_LABEL__(i_) case CO_LINE_ID__(i_)
  #define CO_STATE__(i_) CO_LINE_ID__(i_)

  #define CO_STATE_DISPATCHER_BEGIN__\
    assert(col__->cop__.co_state__ != CO_STATE_JOINED__);\
    switch (col__->cop__.co_state__) { case CO_STATE_NEW__:

  #define CO_STATE_DISPATCHER_END__ } col__->cop__.co_state__ = CO_STATE_JOINED__;

#endif /* CO_USE_RUNTIME_GOTO */

/****************************************************************************************/
/* Locals and parameters */

#define COP_TYPE__(f_) struct MLB_PP_CONCAT(CoParams__, f_)
#define COL_TYPE__(f_) struct MLB_PP_CONCAT(CoLocals__, f_)

#define COL_BEGIN_STATIC__(f_, ...)\
  COP_TYPE__(f_) { CoState__ co_state__; CO_PP_SEMIS(__VA_ARGS__) };\
  COL_TYPE__(f_) {\
    COP_TYPE__(f_) cop__;\
    struct
/* 'co_state__' is made a member of 'cop__' just to avoid dealing with an empty 
   struct type when there are no params */

#define COL_BEGIN_DYNAMIC__(f_, ...)\
  COP_TYPE__(f_) { CoState__ co_state__; CO_PP_SEMIS(__VA_ARGS__) };\
  COL_TYPE__(f_) {\
    COP_TYPE__(f_) cop__;\
    CoByte *co_persistent_brk__;\
    struct
/* Functions that support 'CO_ALLOCA' need a persistent pointer to the current top of the 
   stack. Functions that do not support 'CO_ALLOCA' can get by with a local non-persistent 
   (calculated) pointer to the current top of the stack */

#define COL_END__ col__; };

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
          CO_DBG_SUSG_ARG(struct CoDbgRootContext__ *const codrc__)\
          COL_TYPE__(f_) *const col__)

#define COL (col__->col__)
#define COP (col__->cop__)

#define CO_PROTOTYPE(f_, ...)\
  COL_TYPE__(f_);\
  CO_PROTOTYPE__(f_);\
  COL_BEGIN_STATIC__(f_, ##__VA_ARGS__)

#define CO_PROTOTYPE_DYNAMIC(f_, ...)\
  COL_TYPE__(f_);\
  CO_PROTOTYPE__(f_);\
  COL_BEGIN_DYNAMIC__(f_, ##__VA_ARGS__)

/* A forward declaration of 'COL_TYPE__(f_)' is made before 'CO_PROTOTYPE__(f_)' to 
   prevent 'COL_TYPE__(f_)' in parameter list from becoming a prototype-scope declaration */

#define CO_PROTOTYPE_END COL_END__

#ifndef _MSC_VER
  #define CO_PROTOTYPE_NO_LOCALS(f_, ...)\
    CO_PROTOTYPE(f_, ##__VA_ARGS__) {} CO_PROTOTYPE_END
#else
  #define CO_PROTOTYPE_NO_LOCALS(f_, ...)\
    CO_PROTOTYPE(f_, ##__VA_ARGS__) { char co_dummy__; } CO_PROTOTYPE_END
#endif

/****************************************************************************************/
/* Function stratup */

/* Bootstrap is performed every time the function is entered, regardless of whether this 
   is the initial call or a context switch. Bootstrap restores calculated local values */

#define CO_BOOTSTRAP_FRAME_STATIC__()\
  CoByte *const co_brk__ = (CoByte *) col__ + sizeof *col__;\
  assert(CO_IN_STACK__(co_brk__));
/* 'co_brk__' is constant */

#define CO_BOOTSTRAP_FRAME_DYNAMIC__()\
  CoByte *co_brk__ = col__->co_persistent_brk__;
/* On initial call 'co_brk__' will end up with a meaningless value from 
   'col__->co_persistent_brk__'. 'CO_SETUP_FRAME_DYNAMIC__' will set both to a valid 
   value. 'co_brk__' is not constant */

/* Initial setup is performed only when the function is called initially (not a return 
   from context switch). It initializes persistent values */

#define CO_SETUP_FRAME_STATIC__()\
  CO_SUSG_ONLY(CO_UPDATE_SUSG__());

#define CO_SETUP_FRAME_DYNAMIC__()\
  co_brk__ = (CoByte *) col__ + sizeof *col__;\
  assert(CO_IN_STACK__(co_brk__));\
  col__->co_persistent_brk__ = co_brk__;\
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

#define CO_FUNCTION_DEFINITION(f_) CO_PROTOTYPE__(f_)

#define CO_BEGIN\
  CO_BOOTSTRAP_FRAME_STATIC__();\
  CO_STATE_DISPATCHER_BEGIN__;\
  CO_SETUP_FRAME_STATIC__();

#define CO_BEGIN_DYNAMIC\
  CO_BOOTSTRAP_FRAME_DYNAMIC__();\
  CO_STATE_DISPATCHER_BEGIN__;\
  CO_SETUP_FRAME_DYNAMIC__();

#define CO_END CO_STATE_DISPATCHER_END__

#define CO_YIELD__(i_) do {\
    col__->cop__.co_state__ = CO_STATE__(i_); return; CO_LABEL__(i_):;\
  } while (0)

#define CO_YIELD() CO_YIELD__(0)
#define CO_RETURN() do { col__->cop__.co_state__ = CO_STATE_JOINED__; return; } while (0)

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
  (assert(col__->co_persistent_brk__ == co_brk__),\
   col__->co_persistent_brk__ = co_brk__ = MLB_STRICT_ALIGN_UP_PTR(co_brk__, align_),\
   col__->co_persistent_brk__ = (co_brk__ += (size_)),\
   assert(CO_IN_STACK__(co_brk__)),\
   CO_SUSG_ARG(CO_UPDATE_SUSG__())\
   (void *) (co_brk__ - (size_)))

#define CO_ZALLOCA(size_, align_) memset(CO_ALLOCA(size_, align_), 0, size_)

#define CO_ALLOCA_T(T_, count_) CO_ALLOCA((STD_ size_t) count_ * sizeof(T_), alignof(T_))  
#define CO_ZALLOCA_T(T_, count_) CO_ZALLOCA((STD_ size_t) count_ * sizeof(T_), alignof(T_))

/****************************************************************************************/

#define COL_NEXT__(f_)\
  ((COL_TYPE__(f_) *) MLB_STRICT_ALIGN_UP_PTR(co_brk__, alignof(COL_TYPE__(f_))))

/* Invoke a co-function from another co-function */
#define CO_INVOKE(f_, ...) do {\
    COL_TYPE__(f_) *col_next__ = COL_NEXT__(f_);\
    assert(CO_IN_STACK__((CoByte *) col_next__ + sizeof *col_next__));\
    col_next__->cop__ = MLB_INITIALIZER(COP_TYPE__(f_), CO_STATE_NEW__, ##__VA_ARGS__ );\
    while (f_(CO_RCON_ARG(corc__) CO_DBG_SUSG_ARG(codrc__) col_next__),\
           col_next__->cop__.co_state__ != CO_STATE_JOINED__) {\
      CO_YIELD();\
      col_next__ = COL_NEXT__(f_);\
    }\
  } while (0)

/****************************************************************************************/

/* "ASP" stands for "alignment/size pair" */

#define CO_SUM_ASPS__(susg_, p_)\
  (MLB_STRICT_ALIGN_UP(susg_, MLB_PP_AT(p_, 0)) + MLB_PP_AT(p_, 1))

#define CO_SUSG(...) MLB_PP_FOLD_L(CO_SUM_ASPS__, 0, ##__VA_ARGS__)
/* Expects pairs '(alignment, size)' for sequential memory consumers */

#define CO_FULL_SUSG(...) CO_SUSG((1, CO_ROOT_SUSG), ##__VA_ARGS__)
/* Stack usage starting from and including root context  */

#define COF_ASP(f_) (alignof(COL_TYPE__(f_)), sizeof(COL_TYPE__(f_)))

#define COF_ASP_M__(f_) , COF_ASP(f_)
#define COF_SUSG(...) CO_SUSG(MLB_PP_APPLY_FM_U(COF_ASP, COF_ASP_M__, ##__VA_ARGS__))
/* Expects a list of co-function names */

#define COF_FULL_SUSG(...)\
  CO_FULL_SUSG(MLB_PP_APPLY_FM_U(COF_ASP, COF_ASP_M__, ##__VA_ARGS__))
/* Stack usage starting from and including root context  */

/****************************************************************************************/

#define CO_ROOT_INVOKE__(id_, stack_, ssize_, f_, ...) do {\
    assert((id_) != 0);\
    \
    CO_REPORT_SSIZE_ONLY(\
      static bool s_co_ssize_reported__;\
      if (!s_co_ssize_reported__) {\
        co_report_ssize__((id_), (ssize_));\
        s_co_ssize_reported__ = true;\
      }\
    )\
    \
    CO_DBG_SUSG_ONLY(\
      static struct CoDbgRootContext__ s_codrc__;\
      if (s_codrc__.co_id__ == 0)\
        s_codrc__ = MLB_INITIALIZER(struct CoDbgRootContext__, (id_), (stack_), (ssize_));\
      struct CoDbgRootContext__ *const codrc__ = &s_codrc__;\
    )\
    \
    CoByte *co_brk__ = (CoByte *) (stack_);\
    assert(MLB_IS_STRICT_ALIGNED_PTR(co_brk__, CO_STACK_ALIGN));\
    \
    CO_RCON_ONLY(\
      CoRootContext *corc__ = (CoRootContext *) co_brk__;\
      co_brk__ += CO_ROOT_SUSG;\
      assert(CO_IN_STACK__(co_brk__));\
    )\
    \
    COL_TYPE__(f_) *col_first__ = COL_NEXT__(f_);\
    assert(CO_IN_STACK__((CoByte *) col_first__ + sizeof *col_first__));\
    if (col_first__->cop__.co_state__ == CO_STATE_JOINED__)\
      break;\
    if (col_first__->cop__.co_state__ == CO_STATE_NEW__) {\
      CO_RCON_ONLY(co_init_root_context(corc__));\
      col_first__->cop__ = MLB_INITIALIZER(COP_TYPE__(f_), CO_STATE_NEW__, ##__VA_ARGS__);\
    }\
    \
    CO_RCON_ONLY(\
      if (!co_process_root_context(corc__))\
        break;\
    )\
    \
    f_(CO_RCON_ARG(corc__) CO_DBG_SUSG_ARG(codrc__) col_first__);\
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

#define CO_ROOT_INVOKE_SSIZE_L(id_, ssize_, f_, ...) do {\
    static alignas(CO_STACK_ALIGN) CoByte co_stack__[ssize_];\
    CO_ROOT_INVOKE__(id_, co_stack__, ssize_, f_, ##__VA_ARGS__);\
  } while (0)

#define CO_ROOT_INVOKE_ASPS_L(id_, asps_, f_, ...)\
  CO_ROOT_INVOKE_SSIZE_L(id_, CO_FULL_SUSG(asps_), f_, ##__VA_ARGS__)

#define CO_ROOT_INVOKE_FS_L(id_, fs_, f_, ...)\
  CO_ROOT_INVOKE_SSIZE_L(id_, COF_FULL_SUSG(MLB_PP_UNWRAP(fs_)), f_, ##__VA_ARGS__)

#define CO_ROOT_INVOKE_L(id_, f_, ...)\
  CO_ROOT_INVOKE_SSIZE_L(id_, COF_FULL_SUSG(f_), f_, ##__VA_ARGS__)

/****************************************************************************************/

#define CO_SUB_ROOT_INVOKE_SSIZE(id_, sub_stack_, sub_ssize_, f_, ...)\
  CO_ROOT_INVOKE__(id_, sub_stack_, sub_ssize_, f_, ##__VA_ARGS__)

/****************************************************************************************/
/* Invocation in a normal program flow: invoked between 'CO_ROOT_BEGIN' and 'CO_ROOT_END', 
   waits till all co-threads complete (i.e. "join"), then continues execution after 
   'CO_ROOT_END' */

#define CO_ROOT_INVOKE_SSIZE(id_, ssize_, f_, ...) do {\
    static alignas(CO_STACK_ALIGN) CoByte co_stack__[ssize_];\
    CoByte *co_brk__ = co_stack__ + CO_ROOT_SUSG;\
    COL_TYPE__(f_) *col_first__ = COL_NEXT__(f_);\
    if (col_first__->cop__.co_state__ != CO_STATE_JOINED__) {\
      if (col_first__->cop__.co_state__ == CO_STATE_NEW__) ++co_entries__;\
      CO_ROOT_INVOKE__(id_, co_stack__, ssize_, f_, ##__VA_ARGS__);\
      if (col_first__->cop__.co_state__ == CO_STATE_JOINED__) --co_entries__;\
    }\
  } while (0)

#define CO_ROOT_INVOKE_ASPS(id_, asps_, f_, ...)\
  CO_ROOT_INVOKE_SSIZE(id_, CO_FULL_SUSG(asps_), f_, ##__VA_ARGS__)

#define CO_ROOT_INVOKE_FS(id_, fs_, f_, ...)\
  CO_ROOT_INVOKE_SSIZE(id_, COF_FULL_SUSG(MLB_PP_UNWRAP(fs_)), f_, ##__VA_ARGS__)

#define CO_ROOT_INVOKE(id_, f_, ...)\
  CO_ROOT_INVOKE_SSIZE(id_, COF_FULL_SUSG(f_), f_, ##__VA_ARGS__)

#define CO_ROOT_BEGIN do { unsigned co_entries__ = 0; do {
#define CO_ROOT_END } while (co_entries__ > 0); } while (0);

#endif /* MLB_CO_H_ */
