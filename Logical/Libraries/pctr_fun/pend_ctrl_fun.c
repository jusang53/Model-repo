/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_ctrl_fun
 * File: pend_ctrl_fun.c
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Wed Mar 17 14:21:47 2010
 ********************************************************************
 * Implementation of program pend_ctrl_fun
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#include "pend_ctrl_fun.h"
#include "pend_ctrl_fun_private.h"

/*  Defines */

/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/*  Declarations  */

/***************************** FILE SCOPE DATA ********************************/

/*************************** FUNCTIONS ****************************************/

/* Model step function */
void pend_ctrl_fun_step(RT_MODEL_pend_ctrl_fun *const pend_ctrl_fun_M, struct pctrFub* inst)
{
  struct BlockIO_pend_ctrl_fun *pend_ctrl_fun_B = ((struct BlockIO_pend_ctrl_fun *)
    pend_ctrl_fun_M->blockIO);
  struct D_Work_pend_ctrl_fun *pend_ctrl_fun_DWork = ((struct D_Work_pend_ctrl_fun *)
    pend_ctrl_fun_M->dwork);
  real_T ref;
  uint16_T err_code;
  boolean_T varargin_1_idx_0;

  /* S-Function (bur_in): '<S1>/Input' */
  pend_ctrl_fun_B->Input = inst->ref;

  /* S-Function (bur_in): '<S4>/Input' */
  pend_ctrl_fun_B->Input_b[0] = inst->x[0];
  pend_ctrl_fun_B->Input_b[1] = inst->x[1];
  pend_ctrl_fun_B->Input_b[2] = inst->x[2];
  pend_ctrl_fun_B->Input_b[3] = inst->x[3];

  /* MATLAB Function: '<Root>/State feedback controller  with error handling' incorporates:
   *  Constant: '<Root>/ref_limit'
   *  Constant: '<Root>/u_limit'
   */
  ref = pend_ctrl_fun_B->Input;

  /* MATLAB Function 'State feedback controller  with error handling': '<S3>:1' */
  /* '<S3>:1:25' */
  err_code = pend_ctrl_fun_DWork->local_err_code;
  varargin_1_idx_0 = (fabs(pend_ctrl_fun_B->Input_b[0]) > 100.0);
  varargin_1_idx_0 = (((int32_T)varargin_1_idx_0 < (fabs
    (pend_ctrl_fun_B->Input_b[1]) > 100.0)) || varargin_1_idx_0);
  varargin_1_idx_0 = (((int32_T)varargin_1_idx_0 < (fabs
    (pend_ctrl_fun_B->Input_b[2]) > 100.0)) || varargin_1_idx_0);
  varargin_1_idx_0 = (((int32_T)varargin_1_idx_0 < (fabs
    (pend_ctrl_fun_B->Input_b[3]) > 100.0)) || varargin_1_idx_0);
  if (varargin_1_idx_0) {
    /* '<S3>:1:27' */
    /* '<S3>:1:28' */
    err_code = 50001U;

    /* '<S3>:1:29' */
    ref = 0.0;
  } else {
    if (pend_ctrl_fun_B->Input > 1.5) {
      /* '<S3>:1:31' */
      /* '<S3>:1:32' */
      err_code = 50013U;

      /* '<S3>:1:33' */
      ref = 1.5;
    } else {
      if (pend_ctrl_fun_B->Input < -1.5) {
        /* '<S3>:1:34' */
        /* '<S3>:1:35' */
        err_code = 50014U;

        /* '<S3>:1:36' */
        ref = -1.5;
      }
    }

    /* '<S3>:1:38' */
    ref = (((2987.4616903679125 * pend_ctrl_fun_B->Input_b[0] +
             3740.1178916812455 * pend_ctrl_fun_B->Input_b[1]) +
            32774.860875805127 * pend_ctrl_fun_B->Input_b[2]) +
           7399.4348019785593 * pend_ctrl_fun_B->Input_b[3]) +
      -2987.4616903679112 * ref;
    if (ref > 10000.0) {
      /* '<S3>:1:39' */
      /* '<S3>:1:40' */
      ref = 10000.0;

      /* '<S3>:1:41' */
      err_code = 50011U;
    } else {
      if (ref < -10000.0) {
        /* '<S3>:1:42' */
        /* '<S3>:1:43' */
        ref = -10000.0;

        /* '<S3>:1:44' */
        err_code = 50012U;
      }
    }
  }

  /* '<S3>:1:47' */
  pend_ctrl_fun_DWork->local_err_code = err_code;
  pend_ctrl_fun_B->u = ref;
  pend_ctrl_fun_B->err_code = err_code;

  /* End of MATLAB Function: '<Root>/State feedback controller  with error handling' */

  /* S-Function (bur_out): '<Root>/Output' */
  inst->err_code = pend_ctrl_fun_B->err_code;

  /* S-Function (bur_in): '<S4>/Input1' */
  pend_ctrl_fun_B->Input1[0] = inst->y[0];
  pend_ctrl_fun_B->Input1[1] = inst->y[1];

  /* S-Function (bur_out): '<S4>/Output' */
  inst->F = pend_ctrl_fun_B->u;
}

/* Model initialize function */
void pend_ctrl_fun_initialize(RT_MODEL_pend_ctrl_fun *const pend_ctrl_fun_M, struct pctrFub* inst)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(pend_ctrl_fun_M);
}

/* Model terminate function */
void pend_ctrl_fun_terminate(RT_MODEL_pend_ctrl_fun *const pend_ctrl_fun_M, struct pctrFub* inst)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(pend_ctrl_fun_M);
}

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
