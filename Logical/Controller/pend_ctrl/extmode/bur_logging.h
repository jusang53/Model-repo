/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * File: bur_logging.h
 * Author: B&R
 * Created: September 07, 2010
 *******************************************************************/

#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
 #include <AsDefault.h>
#endif

#ifndef TRUE
# define TRUE  (1U)
#endif

#ifndef FALSE
# define FALSE (0U)
#endif

/** public datatypes **/

/*  The three different types of log- entries
    according to the three types of log- entries
    in 'AsArLog'. */
typedef enum
{
	logLevel_info,
	logLevel_warning,
	logLevel_fatal
}logLevel_t;

/** end public datatypes **/


/** public function prototypes **/

/* call this function to add a new logging- entry */
BOOL writeLogEntry( logLevel_t logLevel,
                    UDINT errornr,
                    const char* string);


/* poll this function to write the entries to the log-files */
UINT loggingWork();

/** end public function prototypes **/
