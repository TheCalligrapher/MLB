#include "../base/mlb_config.h"

#define noCO_TRACK_STACK_USAGE
/* Enables debug report of maximum stack depth for each co-root, regardless of the current 
   'NDEBUG' setting. The report will include the maximum current co-stack usage for the 
   current configuration. The report is made through 'g_co_susg_reporter' callback */

#define noCO_REPORT_STACK_SIZE
/* Enables debug report of co-stack allocated for each co-root, regardless of the current 
   'NDEBUG' setting. The report is made through 'g_co_ssize_reporter' callback */

#define CO_ENABLE_ROOT_CONTEXT
/* If enabled, the client translation unit shall also supply

  * 'CoRootContext' type
  * 'void co_init_root_context(CoRootContext *)' function
  * 'bool co_process_root_context(CoRootContext *)' function */
