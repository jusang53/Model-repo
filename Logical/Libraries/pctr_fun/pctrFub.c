/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_ctrl_fun
 * File: pctrFub.c
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Wed Mar 17 14:21:47 2010
 ********************************************************************
 * Implementation of program pend_ctrl_fun
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#include <bur/plctypes.h>
#include "pend_ctrl_fun.h"
#include "rtwtypes.h"

/* Defines */
#define SS_TERMINATE 4
#define SS_OUTPUT 3
#define SS_INITIALIZE 2


/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/*  Declarations  */

/***************************** FILE SCOPE DATA ********************************/

/*************************** FUNCTIONS ****************************************/
#ifdef __cplusplus

unsigned long bur_heap_size = 6553500;

#endif

/*LEGACYMODE_VARIABLES*/
void pctrFub(struct pctrFub* inst)
{
  tag_RTM_pend_ctrl_fun* const pend_ctrl_fun_M = &(inst)->bur_pend_ctrl_fun;
	inst->bur_pend_ctrl_fun.blockIO = &(inst)->bur_BlockIO_pend_ctrl_fun;
	inst->bur_pend_ctrl_fun.dwork = &(inst)->bur_D_Work_pend_ctrl_fun;
	
  switch (inst->ssMethodType)
  {
   case SS_INITIALIZE:
    /* call model initialize function */
    pend_ctrl_fun_initialize(pend_ctrl_fun_M, inst);
    break;

   case SS_OUTPUT:
    /* call model step function */
    pend_ctrl_fun_step(pend_ctrl_fun_M, inst);

    
    break;

   case SS_TERMINATE:
    /* call model terminate function */
    pend_ctrl_fun_terminate(pend_ctrl_fun_M, inst);
    break;
  }
}

/*****************************************************************************
   Function block sample time: 0.01s
 *****************************************************************************/

/*****************************************************************************
   B&R Automation Studio Target for Simulink Version: A6.1.0 (06-Nov-2019)
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
 * image_toolbox                                                              *
 * matlab                                                                     *
 * matlab_coder                                                               *
 * opc_toolbox                                                                *
 * real-time_workshop                                                         *
 * rtw_embedded_coder                                                         *
 * simulink                                                                   *
 *============================================================================*/
