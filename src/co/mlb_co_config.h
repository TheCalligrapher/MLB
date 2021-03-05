#include "../base/mlb_config.h"

#ifndef CO_TRACK_STACK_USAGE
  #define CO_TRACK_STACK_USAGE 0
#endif 
/* Enables debug report of maximum stack depth for each co-root, regardless of the current 
   'NDEBUG' setting. The report will include the maximum current co-stack usage for the 
   current configuration. The report is made through 'g_co_susg_reporter' callback */

#ifndef CO_REPORT_STACK_SIZE
  #define CO_REPORT_STACK_SIZE 0
#endif 
/* Enables debug report of co-stack allocated for each co-root, regardless of the current 
   'NDEBUG' setting. The report is made through 'g_co_ssize_reporter' callback */

#ifndef CO_ENABLE_ROOT_CONTEXT
  #define CO_ENABLE_ROOT_CONTEXT 1
#endif 
/* If enabled, the client translation unit shall also supply

  * 'CoRootContext' type
  * 'void co_init_root_context(CoRootContext *)' function
  * 'bool co_process_root_context(CoRootContext *)' function */

#ifndef CO_USE_RUNTIME_GOTO
  #ifdef __GNUC__
    #define CO_USE_RUNTIME_GOTO 1
  #else
    #define CO_USE_RUNTIME_GOTO 0
  #endif
#endif 
