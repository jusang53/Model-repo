/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_ctrl_lin
 * File: pend_ctrl_lin.h
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Wed Mar 17 14:21:47 2010
 ********************************************************************
 * Header for program pend_ctrl_lin
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#ifndef RTW_HEADER_pend_ctrl_lin_h_
#define RTW_HEADER_pend_ctrl_lin_h_
#ifndef pend_ctrl_lin_COMMON_INCLUDES_
# define pend_ctrl_lin_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* pend_ctrl_lin_COMMON_INCLUDES_ */

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
 #include <AsDefault.h>
#endif

#ifndef AST_ROUND
#define AST_ROUND(x) ((x)>=0?(long long)((x)+0.5):(long long)((x)-0.5))
#endif

#include "pend_ctrl_lin_types.h"


/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef MIN
#define MIN(a,b)                       ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)                       ((a) > (b) ? (a) : (b))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Input;                        /* '<S1>/Input' */
  real_T ref;                          /* '<Root>/ref' */
  real_T FeedForward;                  /* '<S4>/Feed-Forward' */
  real_T Input_f[4];                   /* '<S3>/Input' */
  real_T LQRController;                /* '<S4>/LQR Controller' */
  real_T Sum;                          /* '<S4>/Sum' */
  real_T Input1[2];                    /* '<S3>/Input1' */
} BlockIO_pend_ctrl_lin;

/* Real-time Model Data Structure */
struct tag_RTM_pend_ctrl_lin {
  const char_T *errorStatus;
};

/* Block signals (default storage) */
extern BlockIO_pend_ctrl_lin pend_ctrl_lin_B;

/* Model entry point functions */
extern void pend_ctrl_lin_initialize(void);
extern void pend_ctrl_lin_output(void);
extern void pend_ctrl_lin_update(void);
extern void pend_ctrl_lin_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pend_ctrl_lin *const pend_ctrl_lin_M;

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
 * '<Root>' : 'pend_ctrl_lin'
 * '<S1>'   : 'pend_ctrl_lin/B&R reference input'
 * '<S2>'   : 'pend_ctrl_lin/Configurable Controller  Subsystem1'
 * '<S3>'   : 'pend_ctrl_lin/inverted_pendulum_IOs'
 * '<S4>'   : 'pend_ctrl_lin/Configurable Controller  Subsystem1/State Feedback Controller (blks)'
 */
#endif                                 /* RTW_HEADER_pend_ctrl_lin_h_ */
