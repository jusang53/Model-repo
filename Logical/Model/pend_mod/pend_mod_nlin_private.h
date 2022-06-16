/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer Industrie-Elektronik Ges.m.b.H.
 ********************************************************************
 * Program: pend_mod_nlin
 * File: pend_mod_nlin_private.h
 * Author: Bernecker + Rainer Industrie Elektronik Ges.m.b.H.
 * Created: Fri Apr 16 22:40:22 2010
 ********************************************************************
 * Header for program pend_mod_nlin
 ********************************************************************
 * Generated with B&R Automation Studio Target for Simulink  V6.1.0
 * (ERT based)
 ********************************************************************/

#ifndef RTW_HEADER_pend_mod_nlin_private_h_
#define RTW_HEADER_pend_mod_nlin_private_h_
#include "rtwtypes.h"
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

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef MIN
#define MIN(a,b)                       ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)                       ((a) > (b) ? (a) : (b))
#endif

/* private model entry point functions */
extern void pend_mod_nlin_derivatives(void);

#endif                                 /* RTW_HEADER_pend_mod_nlin_private_h_ */
