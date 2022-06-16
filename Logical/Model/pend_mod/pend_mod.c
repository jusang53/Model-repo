/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_mod_nlin
 * File: pend_mod.c
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Fri Apr 16 22:40:22 2010
 ********************************************************************
 * Implementation of program pend_mod_nlin
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#define _ASMATH_
#define ASMATH_
#define _ASMATH_H
#define ASMATH_H
#define _ASMATH_H_
#define ASMATH_H_
#define _ASSTRING_
#define ASSTRING_
#define _ASSTRING_H
#define ASSTRING_H
#define _ASSTRING_H_
#define ASSTRING_H_
#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "pend_mod_nlin.h"
#include "rtwtypes.h"

/*  Defines */

/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/*  Declarations  */

/***************************** FILE SCOPE DATA ********************************/

/*************************** FUNCTIONS ****************************************/
#ifdef __cplusplus

unsigned long bur_heap_size = 6553500;

#endif


  void _INIT mainINIT(void)
{
  
    UDINT st_ident;
  RTInfo_typ rt_info;
  rt_info.enable = 1;
  RTInfo(&rt_info);
  if (rt_info.cycle_time != 10000) {
    /* cycle time does not match Simulink fixed-step size */
    ST_ident("pend_mod", 0, &st_ident);
    ST_tmp_suspend(st_ident);
    ERR_warning(33310, 0);
  }

  /* initialize model */
  pend_mod_nlin_initialize();
  
} void _CYCLIC mainCYCLIC(void)
{
	if(start)
	{/* call model step function */
		pend_mod_nlin_output();
		pend_mod_nlin_update();
	}
	if(reset)
	{
		start = 0;
		pend_mod_nlin_initialize();
		ref = 0;
		x[0] = x[1] = x[2] = x[3] = 0;
		y[0] = y[1] = 0;
		F = 0;
		reset = 0;
	}
}  void _EXIT mainEXIT(void)
{
  /* terminate model */
  pend_mod_nlin_terminate();
  
} /*****************************************************************************
     Task sample time: 0.01s
   *****************************************************************************/
/*****************************************************************************
   B&R Automation Studio Target for Simulink Version: V6.1.0 (06-Nov-2019)
 *****************************************************************************/

/*======================== TOOL VERSION INFORMATION ==========================*
 * MATLAB 9.7 (R2019b)18-Jul-2019                                             *
 * Simulink 10.0 (R2019b)18-Jul-2019                                          *
 * Simulink Coder 9.2 (R2019b)18-Jul-2019                                     *
 * Embedded Coder 7.3 (R2019b)18-Jul-2019                                     *
 * Stateflow 10.1 (R2019b)18-Jul-2019                                         *
 * Fixed-Point Designer 6.4 (R2019b)18-Jul-2019                               *
 *============================================================================*/

/*======================= LICENSE IN USE INFORMATION =========================*
 * control_toolbox                                                            *
 * matlab                                                                     *
 * matlab_coder                                                               *
 * real-time_workshop                                                         *
 * rtw_embedded_coder                                                         *
 * simulink                                                                   *
 *============================================================================*/
