/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_ctrl_lin
 * File: pend_ctrl.c
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Wed Mar 17 14:21:47 2010
 ********************************************************************
 * Implementation of program pend_ctrl_lin
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

#include "pend_ctrl_lin.h"
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
    ST_ident("pend_ctrl", 0, &st_ident);
    ST_tmp_suspend(st_ident);
    ERR_warning(33310, 0);
  }

  /* initialize model */
  pend_ctrl_lin_initialize();
  
} void _CYCLIC mainCYCLIC(void)
{
  /* call model step function */
  pend_ctrl_lin_output();

  
  pend_ctrl_lin_update();
  
} void _EXIT mainEXIT(void)
{
  /* terminate model */
  pend_ctrl_lin_terminate();
  
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
