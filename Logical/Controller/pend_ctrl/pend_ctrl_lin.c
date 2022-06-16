/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_ctrl_lin
 * File: pend_ctrl_lin.c
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Wed Mar 17 14:21:47 2010
 ********************************************************************
 * Implementation of program pend_ctrl_lin
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#include "pend_ctrl_lin.h"
#include "pend_ctrl_lin_private.h"

/*  Defines */

/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/* Block signals (default storage) */
BlockIO_pend_ctrl_lin pend_ctrl_lin_B;

/* Real-time model */
RT_MODEL_pend_ctrl_lin pend_ctrl_lin_M_;
RT_MODEL_pend_ctrl_lin *const pend_ctrl_lin_M = &pend_ctrl_lin_M_;

/*  Declarations  */

/***************************** FILE SCOPE DATA ********************************/

/*************************** FUNCTIONS ****************************************/

/* Model output function */
void pend_ctrl_lin_output(void)
{
  real_T tmp;

  /* S-Function (bur_in): '<S1>/Input' */
  pend_ctrl_lin_B.Input = ref;

  /* Gain: '<Root>/ref' */
  pend_ctrl_lin_B.ref = 10.0 * pend_ctrl_lin_B.Input;

  /* Gain: '<S4>/Feed-Forward' */
  pend_ctrl_lin_B.FeedForward = -2987.4616903679112 * pend_ctrl_lin_B.ref;

  /* S-Function (bur_in): '<S3>/Input' */
  pend_ctrl_lin_B.Input_f[0] = x[0];
  pend_ctrl_lin_B.Input_f[1] = x[1];
  pend_ctrl_lin_B.Input_f[2] = x[2];
  pend_ctrl_lin_B.Input_f[3] = x[3];

  /* Gain: '<S4>/LQR Controller' */
  tmp = -2987.4616903679125 * pend_ctrl_lin_B.Input_f[0];
  tmp += -3740.1178916812455 * pend_ctrl_lin_B.Input_f[1];
  tmp += -32774.860875805127 * pend_ctrl_lin_B.Input_f[2];
  tmp += -7399.4348019785593 * pend_ctrl_lin_B.Input_f[3];
  pend_ctrl_lin_B.LQRController = tmp;

  /* Sum: '<S4>/Sum' */
  pend_ctrl_lin_B.Sum = pend_ctrl_lin_B.FeedForward -
    pend_ctrl_lin_B.LQRController;

  /* S-Function (bur_in): '<S3>/Input1' */
  pend_ctrl_lin_B.Input1[0] = y[0];
  pend_ctrl_lin_B.Input1[1] = y[1];

  /* S-Function (bur_out): '<S3>/Output' */
  F = pend_ctrl_lin_B.Sum;
}

/* Model update function */
void pend_ctrl_lin_update(void)
{
  /* (no update code required) */
}

/* Model initialize function */
void pend_ctrl_lin_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void pend_ctrl_lin_terminate(void)
{
  /* (no terminate code required) */
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
 * matlab                                                                     *
 * matlab_coder                                                               *
 * real-time_workshop                                                         *
 * rtw_embedded_coder                                                         *
 * simulink                                                                   *
 *============================================================================*/
