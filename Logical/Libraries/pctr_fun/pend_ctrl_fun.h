/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_ctrl_fun
 * File: pend_ctrl_fun.h
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Wed Mar 17 14:21:47 2010
 ********************************************************************
 * Header for program pend_ctrl_fun
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#ifndef RTW_HEADER_pend_ctrl_fun_h_
#define RTW_HEADER_pend_ctrl_fun_h_
#include <math.h>
#ifndef pend_ctrl_fun_COMMON_INCLUDES_
# define pend_ctrl_fun_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* pend_ctrl_fun_COMMON_INCLUDES_ */

#include "pend_ctrl_fun_types.h"
#include "pctr_fun.h"
/* Beginning of Dynamic TypeDefs: */
/* End of Dynamic TypeDefs: */
#ifndef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#endif

#ifndef AST_ROUND
#define AST_ROUND(x) ((x)>=0?(long long)((x)+0.5):(long long)((x)-0.5))
#endif

#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

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

/* Block states (default storage) for system '<Root>' */

/* Real-time Model Data Structure */

/* Model entry point functions */
extern void pend_ctrl_fun_initialize(RT_MODEL_pend_ctrl_fun *const
  pend_ctrl_fun_M, struct pctrFub* inst);
extern void pend_ctrl_fun_step(RT_MODEL_pend_ctrl_fun *const pend_ctrl_fun_M, struct pctrFub* inst);
extern void pend_ctrl_fun_terminate(RT_MODEL_pend_ctrl_fun *const
  pend_ctrl_fun_M, struct pctrFub* inst);

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
 * '<Root>' : 'pend_ctrl_fun'
 * '<S1>'   : 'pend_ctrl_fun/B&R reference input'
 * '<S2>'   : 'pend_ctrl_fun/Inverted Pendulum (Simulation // IOs)'
 * '<S3>'   : 'pend_ctrl_fun/State feedback controller  with error handling'
 * '<S4>'   : 'pend_ctrl_fun/Inverted Pendulum (Simulation // IOs)/inverted_pendulum_IOs'
 */
#endif                                 /* RTW_HEADER_pend_ctrl_fun_h_ */
