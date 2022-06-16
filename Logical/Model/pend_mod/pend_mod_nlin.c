/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_mod_nlin
 * File: pend_mod_nlin.c
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Fri Apr 16 22:40:22 2010
 ********************************************************************
 * Implementation of program pend_mod_nlin
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#include "pend_mod_nlin.h"
#include "pend_mod_nlin_private.h"

/*  Defines */

/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/* Block signals (default storage) */
BlockIO_pend_mod_nlin pend_mod_nlin_B;

/* Continuous states */
ContinuousStates_pend_mod_nlin pend_mod_nlin_X;

/* Real-time model */
RT_MODEL_pend_mod_nlin pend_mod_nlin_M_;
RT_MODEL_pend_mod_nlin *const pend_mod_nlin_M = &pend_mod_nlin_M_;

/*  Declarations  */

/***************************** FILE SCOPE DATA ********************************/

/*************************** FUNCTIONS ****************************************/

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  pend_mod_nlin_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void pend_mod_nlin_output(void)
{
  real_T x_tmp;
  real_T vdot_tmp;
  real_T vdot_tmp_0;
  if (rtmIsMajorTimeStep(pend_mod_nlin_M)) {
    /* set solver stop time */
    if (!(pend_mod_nlin_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&pend_mod_nlin_M->solverInfo,
                            ((pend_mod_nlin_M->Timing.clockTickH0 + 1) *
        pend_mod_nlin_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&pend_mod_nlin_M->solverInfo,
                            ((pend_mod_nlin_M->Timing.clockTick0 + 1) *
        pend_mod_nlin_M->Timing.stepSize0 + pend_mod_nlin_M->Timing.clockTickH0 *
        pend_mod_nlin_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(pend_mod_nlin_M)) {
    pend_mod_nlin_M->Timing.t[0] = rtsiGetT(&pend_mod_nlin_M->solverInfo);
  }

  /* Integrator: '<S1>/x_dot' */
  pend_mod_nlin_B.x_dot = pend_mod_nlin_X.x_dot_CSTATE;

  /* Integrator: '<S1>/theta_dot' */
  pend_mod_nlin_B.theta_dot = pend_mod_nlin_X.theta_dot_CSTATE;

  /* S-Function (bur_out): '<Root>/Output' */
  y[0] = pend_mod_nlin_B.x_dot;
  y[1] = pend_mod_nlin_B.theta_dot;

  /* Integrator: '<S1>/v_dot' */
  pend_mod_nlin_B.v_dot = pend_mod_nlin_X.v_dot_CSTATE;

  /* Integrator: '<S1>/omega_dot' */
  pend_mod_nlin_B.omega_dot = pend_mod_nlin_X.omega_dot_CSTATE;

  /* S-Function (bur_out): '<Root>/Output1' */
  x[0] = pend_mod_nlin_B.x_dot;
  x[1] = pend_mod_nlin_B.v_dot;
  x[2] = pend_mod_nlin_B.theta_dot;
  x[3] = pend_mod_nlin_B.omega_dot;

  /* S-Function (bur_in): '<Root>/Input' */
  pend_mod_nlin_B.Input = F;

  /* MATLAB Function: '<S1>/Inverted Pendulum  (Non-linear model)' */
  /* MATLAB Function 'inverted_pendulum_embm/Inverted Pendulum  (Non-linear model)': '<S2>:1' */
  /* '<S2>:1:4' */
  x_tmp = sin(pend_mod_nlin_B.theta_dot);
  vdot_tmp = cos(pend_mod_nlin_B.theta_dot);
  vdot_tmp_0 = x_tmp * x_tmp * 0.1 + 1000.0;
  pend_mod_nlin_B.vdot = ((pend_mod_nlin_B.omega_dot * pend_mod_nlin_B.omega_dot
    * 0.05 * x_tmp + -0.98100000000000009 * x_tmp * vdot_tmp) +
    pend_mod_nlin_B.Input) / vdot_tmp_0;

  /* '<S2>:1:5' */
  pend_mod_nlin_B.omegadot = (((9810.9810000000016 * x_tmp - 0.0 *
    pend_mod_nlin_B.omega_dot) - vdot_tmp * pend_mod_nlin_B.Input) -
    pend_mod_nlin_B.omega_dot * pend_mod_nlin_B.omega_dot * 0.05 * sin
    (pend_mod_nlin_B.theta_dot) * vdot_tmp) / vdot_tmp_0 / 0.5;
  if (rtmIsMajorTimeStep(pend_mod_nlin_M)) {
  }
}

/* Model update function */
void pend_mod_nlin_update(void)
{
  if (rtmIsMajorTimeStep(pend_mod_nlin_M)) {
    rt_ertODEUpdateContinuousStates(&pend_mod_nlin_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++pend_mod_nlin_M->Timing.clockTick0)) {
    ++pend_mod_nlin_M->Timing.clockTickH0;
  }

  pend_mod_nlin_M->Timing.t[0] = rtsiGetSolverStopTime
    (&pend_mod_nlin_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    pend_mod_nlin_M->Timing.clockTick1++;
    if (!pend_mod_nlin_M->Timing.clockTick1) {
      pend_mod_nlin_M->Timing.clockTickH1++;
    }
  }
}

/* Derivatives for root system: '<Root>' */
void pend_mod_nlin_derivatives(void)
{
  StateDerivatives_pend_mod_nlin *_rtXdot;
  _rtXdot = ((StateDerivatives_pend_mod_nlin *) pend_mod_nlin_M->derivs);

  /* Derivatives for Integrator: '<S1>/x_dot' */
  _rtXdot->x_dot_CSTATE = pend_mod_nlin_B.v_dot;

  /* Derivatives for Integrator: '<S1>/theta_dot' */
  _rtXdot->theta_dot_CSTATE = pend_mod_nlin_B.omega_dot;

  /* Derivatives for Integrator: '<S1>/v_dot' */
  _rtXdot->v_dot_CSTATE = pend_mod_nlin_B.vdot;

  /* Derivatives for Integrator: '<S1>/omega_dot' */
  _rtXdot->omega_dot_CSTATE = pend_mod_nlin_B.omegadot;
}

/* Model initialize function */
void pend_mod_nlin_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&pend_mod_nlin_M->solverInfo,
                          &pend_mod_nlin_M->Timing.simTimeStep);
    rtsiSetTPtr(&pend_mod_nlin_M->solverInfo, &rtmGetTPtr(pend_mod_nlin_M));
    rtsiSetStepSizePtr(&pend_mod_nlin_M->solverInfo,
                       &pend_mod_nlin_M->Timing.stepSize0);
    rtsiSetdXPtr(&pend_mod_nlin_M->solverInfo, &pend_mod_nlin_M->derivs);
    rtsiSetContStatesPtr(&pend_mod_nlin_M->solverInfo, (real_T **)
                         &pend_mod_nlin_M->contStates);
    rtsiSetNumContStatesPtr(&pend_mod_nlin_M->solverInfo,
      &pend_mod_nlin_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&pend_mod_nlin_M->solverInfo,
      &pend_mod_nlin_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&pend_mod_nlin_M->solverInfo,
      &pend_mod_nlin_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&pend_mod_nlin_M->solverInfo,
      &pend_mod_nlin_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&pend_mod_nlin_M->solverInfo, (&rtmGetErrorStatus
      (pend_mod_nlin_M)));
    rtsiSetRTModelPtr(&pend_mod_nlin_M->solverInfo, pend_mod_nlin_M);
  }

  rtsiSetSimTimeStep(&pend_mod_nlin_M->solverInfo, MAJOR_TIME_STEP);
  pend_mod_nlin_M->intgData.f[0] = pend_mod_nlin_M->odeF[0];
  pend_mod_nlin_M->contStates = ((ContinuousStates_pend_mod_nlin *)
    &pend_mod_nlin_X);
  rtsiSetSolverData(&pend_mod_nlin_M->solverInfo, (void *)
                    &pend_mod_nlin_M->intgData);
  rtsiSetSolverName(&pend_mod_nlin_M->solverInfo,"ode1");
  rtmSetTPtr(pend_mod_nlin_M, &pend_mod_nlin_M->Timing.tArray[0]);
  pend_mod_nlin_M->Timing.stepSize0 = 0.01;

  /* InitializeConditions for Integrator: '<S1>/x_dot' */
  pend_mod_nlin_X.x_dot_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/theta_dot' */
  pend_mod_nlin_X.theta_dot_CSTATE = 0.01;

  /* InitializeConditions for Integrator: '<S1>/v_dot' */
  pend_mod_nlin_X.v_dot_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/omega_dot' */
  pend_mod_nlin_X.omega_dot_CSTATE = 0.0;
}

/* Model terminate function */
void pend_mod_nlin_terminate(void)
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
