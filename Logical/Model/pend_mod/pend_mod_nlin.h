/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_mod_nlin
 * File: pend_mod_nlin.h
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Fri Apr 16 22:40:22 2010
 ********************************************************************
 * Header for program pend_mod_nlin
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#ifndef RTW_HEADER_pend_mod_nlin_h_
#define RTW_HEADER_pend_mod_nlin_h_
#include <math.h>
#ifndef pend_mod_nlin_COMMON_INCLUDES_
# define pend_mod_nlin_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* pend_mod_nlin_COMMON_INCLUDES_ */

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
 #include <AsDefault.h>
#endif

#ifndef AST_ROUND
#define AST_ROUND(x) ((x)>=0?(long long)((x)+0.5):(long long)((x)-0.5))
#endif

#include "pend_mod_nlin_types.h"


/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef MIN
#define MIN(a,b)                       ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)                       ((a) > (b) ? (a) : (b))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T x_dot;                        /* '<S1>/x_dot' */
  real_T theta_dot;                    /* '<S1>/theta_dot' */
  real_T v_dot;                        /* '<S1>/v_dot' */
  real_T omega_dot;                    /* '<S1>/omega_dot' */
  real_T Input;                        /* '<Root>/Input' */
  real_T vdot;                /* '<S1>/Inverted Pendulum  (Non-linear model)' */
  real_T omegadot;            /* '<S1>/Inverted Pendulum  (Non-linear model)' */
} BlockIO_pend_mod_nlin;

/* Continuous states (default storage) */
typedef struct {
  real_T x_dot_CSTATE;                 /* '<S1>/x_dot' */
  real_T theta_dot_CSTATE;             /* '<S1>/theta_dot' */
  real_T v_dot_CSTATE;                 /* '<S1>/v_dot' */
  real_T omega_dot_CSTATE;             /* '<S1>/omega_dot' */
} ContinuousStates_pend_mod_nlin;

/* State derivatives (default storage) */
typedef struct {
  real_T x_dot_CSTATE;                 /* '<S1>/x_dot' */
  real_T theta_dot_CSTATE;             /* '<S1>/theta_dot' */
  real_T v_dot_CSTATE;                 /* '<S1>/v_dot' */
  real_T omega_dot_CSTATE;             /* '<S1>/omega_dot' */
} StateDerivatives_pend_mod_nlin;

/* State disabled  */
typedef struct {
  boolean_T x_dot_CSTATE;              /* '<S1>/x_dot' */
  boolean_T theta_dot_CSTATE;          /* '<S1>/theta_dot' */
  boolean_T v_dot_CSTATE;              /* '<S1>/v_dot' */
  boolean_T omega_dot_CSTATE;          /* '<S1>/omega_dot' */
} StateDisabled_pend_mod_nlin;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_pend_mod_nlin {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  ContinuousStates_pend_mod_nlin *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][4];
  ODE1_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern BlockIO_pend_mod_nlin pend_mod_nlin_B;

/* Continuous states (default storage) */
extern ContinuousStates_pend_mod_nlin pend_mod_nlin_X;

/* Model entry point functions */
extern void pend_mod_nlin_initialize(void);
extern void pend_mod_nlin_output(void);
extern void pend_mod_nlin_update(void);
extern void pend_mod_nlin_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pend_mod_nlin *const pend_mod_nlin_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pend_mod_nlin'
 * '<S1>'   : 'pend_mod_nlin/inverted_pendulum_embm'
 * '<S2>'   : 'pend_mod_nlin/inverted_pendulum_embm/Inverted Pendulum  (Non-linear model)'
 */
#endif                                 /* RTW_HEADER_pend_mod_nlin_h_ */
