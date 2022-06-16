/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * File: bur_logging.c
 * Author: B&R
 * Created: September 07, 2010
 * Abstract: This is a simple logger module to log data by using
 * the library 'AsArLog'. The needed FBK's work asynchronously so
 * buffering the entries is necessary. The buffer 'entry_buffer'
 * is realized as FIFO- buffer (circular- buffer) an is able to
 * contain 'NUM_LOG_ENTRIES' entries at once (per default 5),
 * each combined with a ASCII- string of 'LOG_STRSIZE' length
 * (per default 128, including the logging- header (modelname plus
 * a few other char's) and trailing zero- byte).
 *******************************************************************/


#include "bur_logging.h"
#include <AsArLog.h>
#include <string.h>

/** defines **/

/*  Ident for the AR logger module to be written.
    The default logger module is base user module "$arlogusr". */
#ifndef LOG_IDENT
# define LOG_IDENT (arlogBASE_USER_LOG_IDENT)
#endif

/* size of the entry- buffer */
#ifndef NUM_LOG_ENTRIES
# define NUM_LOG_ENTRIES (5U)
#endif

/* length of ascii- string per log- entry */
#ifndef LOG_STRSIZE
# define LOG_STRSIZE (128U)
#endif

#ifndef MODEL
# define MODEL no_modelname_specified
#endif

/* Get Modelname as string (used for the logging- header) */
#define MODEL_STRING GET_STRING(MODEL)

/* needed to expand the modelname */
#define GET_STRING(arg) GET_STRING1(arg)
#define GET_STRING1(arg) #arg

/** typedefs **/

/* Container for one log- etnry */
typedef struct
{
    logLevel_t  logLevel;
    UDINT       errornr;
    char        asciiString[LOG_STRSIZE];
}logEntry_t;

/** local data **/

static AsArLogWrite_typ 	logWrite_var;

/*  Entry- buffer to temporary store entries before written
    to a logger module */
static logEntry_t entry_buffer[NUM_LOG_ENTRIES];

/*  buffer_first marks the position of the next entry to be
    written to a logger module. (The 'begin' or 'start' of
    the circular- buffer)

    buffer_load is the number of entries currently stored in
    the entry buffer */
static size_t buffer_first = 0, buffer_load = 0;

/** end local data **/


/** local function prototypes **/

static void init_writeFirst();
static void createLogHeader(char *string);

/** end local function prototypes **/


/** public functions **/

BOOL writeLogEntry( logLevel_t logLevel,
                    UDINT errornr,
                    const char* string)
{
    if(buffer_load < NUM_LOG_ENTRIES)
    { /* There's still some space available in the buffer,
         so write the logging information */

        /*  Remaining chars exkluding the trailing zero- byte */
        size_t charsRemaining;

        /* Index to store data into (next free position) */
        size_t tmpIndex = (buffer_first+buffer_load)%NUM_LOG_ENTRIES;
        logEntry_t *tmpEntry = &entry_buffer[tmpIndex];

        /* copy logLevel to the buffer */
        switch(logLevel)
        {
            case logLevel_info:
                tmpEntry->logLevel = arlogLEVEL_INFO;
                break;

            case logLevel_warning:
                tmpEntry->logLevel = arlogLEVEL_WARNING;
                break;

            case logLevel_fatal:
                tmpEntry->logLevel = arlogLEVEL_FATAL;
                break;

            default:
                tmpEntry->logLevel = arlogLEVEL_INFO;
                break;
        }

        /* copy errornr to the buffer */
        tmpEntry->errornr  = errornr;

        /* Create the log- header:  "Model 'Modelname': "   */
        createLogHeader(tmpEntry->asciiString);

        charsRemaining = LOG_STRSIZE - (strlen(tmpEntry->asciiString)+1);

        /* copy string (if present) to the buffer */
        if( (string != NULL) && (charsRemaining > 0) )
        {
            /* copy the error- string to the buffer */
            strncat(tmpEntry->asciiString, string, charsRemaining);
        }

        /* assure that the string is at least null- terminated */
        tmpEntry->asciiString[LOG_STRSIZE-1] = '\0';

        buffer_load++;
        return TRUE;
    }
    /* 'else' the buffer is full, so return FALSE */
    return FALSE;
}

UINT loggingWork()
{
    static BOOL logInProgress = FALSE;
    long count=0;

    for(count=0; count<2; count++)
    {
        if(logInProgress)
        {   /*  logging is currently in progress
                --> call the FBK */
            AsArLogWrite(&logWrite_var);
            if(logWrite_var.status == ERR_OK); /* do nothing */
            else if(logWrite_var.status == ERR_FUB_BUSY)
            {
                /*  FBK is busy --> retry next time */
                return ERR_FUB_BUSY;

            }
            else
            {
                /* an error occurred somewhere */
                return logWrite_var.status;
            }

            /* ERR_OK */
            buffer_load--;
            buffer_first = (buffer_first+1) % NUM_LOG_ENTRIES;
            logInProgress = FALSE;
        }

        /* no logging in progress --> check if there's another entry in the buffer */
        if(buffer_load > 0)
        {
            init_writeFirst();
            logInProgress = TRUE;
        }

    } /* end for(...) */

    return (logInProgress ? ERR_FUB_BUSY : ERR_OK);

} /* end loggingWork() */

/** end public functions **/


/** local functions **/

/*  Initialize the instance- variable of the AsArLogWrite(...) FBK
    with the next entry from the entry- buffer */
static void init_writeFirst()
{
	logWrite_var.enable 	= TRUE;
	logWrite_var.ident		= LOG_IDENT;
	logWrite_var.logLevel	= entry_buffer[buffer_first].logLevel;
	logWrite_var.errornr	= entry_buffer[buffer_first].errornr;
	logWrite_var.mem		= (UDINT)NULL;
	logWrite_var.len		= 0;
	logWrite_var.asciiString= (UDINT)entry_buffer[buffer_first].asciiString;
}

static void createLogHeader(char *string)
{
/*  Remaining chars exkluding the trailing zero- byte */
    size_t charsRemaining;

    if(string == NULL)return;

    /* mark as empty string */
    string[0] = '\0';
    strcat(string, "Model \'");

    /*  remaining chars. The '1' in (strlen(string)+1)
        is for the trailing zero- byte */
    charsRemaining = LOG_STRSIZE - (strlen(string)+1);
    if(charsRemaining > 0)
        strncat(string, MODEL_STRING, charsRemaining);

    charsRemaining = LOG_STRSIZE - (strlen(string)+1);
    if(charsRemaining > 0)
        strncat(string, "\': ", charsRemaining);
}

/** end local functions **/
