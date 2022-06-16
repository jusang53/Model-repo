/*  File    : csfunc_pend.c
 *  Abstract:
 *
 *      Example C-file S-function for defining a continuous system.  
 *
 *      x' = Ax + Bu
 *      y  = Cx + Du
 *
 *      For more details about S-functions, see simulink/src/sfuntmpl_doc.c.
 * 
 *  Copyright 1990-2004 The MathWorks, Inc.
 *  $Revision: 1.9.4.3 $
 */


#define S_FUNCTION_NAME csfunc_pend
#define S_FUNCTION_LEVEL 2

#include <math.h>
#include "simstruc.h"

#define U(element) (*uPtrs[element])  /* Pointer to Input Port0 */


#define G_IDX 0
#define G_PARAM(S) ssGetSFcnParam(S,G_IDX)
#define MM_IDX 1
#define MM_PARAM(S) ssGetSFcnParam(S,MM_IDX)
#define M_IDX 2
#define M_PARAM(S) ssGetSFcnParam(S,M_IDX)
#define L_IDX 3
#define L_PARAM(S) ssGetSFcnParam(S,L_IDX)
#define D_IDX 4
#define D_PARAM(S) ssGetSFcnParam(S,D_IDX)
#define X0_IDX 5
#define X0_PARAM(S) ssGetSFcnParam(S,X0_IDX)



/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 6);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }

    ssSetNumContStates(S, 4);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 0);

    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 4);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy that we have a continuous sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);         
}

#define MDL_INITIALIZE_CONDITIONS
/* Function: mdlInitializeConditions ========================================
 * Abstract:
 *    Initialize both continuous states to zero.
 */
static void mdlInitializeConditions(SimStruct *S)
{
    real_T          *x0     = ssGetContStates(S);
    const real_T    *X0pr    = mxGetPr(X0_PARAM(S));
    
    x0[0] = X0pr[0];
    x0[1] = X0pr[1];
    x0[2] = X0pr[2];
    x0[3] = X0pr[3];
}



/* Function: mdlOutputs =======================================================
 * Abstract:
 *      y = Cx + Du 
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T            *y    = ssGetOutputPortRealSignal(S,0);
    real_T            *x    = ssGetContStates(S);
    int_T  lp;
 
    UNUSED_ARG(tid); /* not used in single tasking mode */

    /* y=x */
    for (lp=0;lp<4;lp++) { 
        y[lp]=x[lp]; 
    }
}



#define MDL_DERIVATIVES
/* Function: mdlDerivatives =================================================
 * Abstract:
 *      xdot = Ax + Bu
 */
static void mdlDerivatives(SimStruct *S)
{
    real_T            *dx   = ssGetdX(S);
    real_T            *x    = ssGetContStates(S);
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    real_T omega, theta, M, m, g, l, d, F;
    const real_T      *Mpr     = mxGetPr(MM_PARAM(S));
    const real_T      *mpr     = mxGetPr(M_PARAM(S));
    const real_T      *gpr     = mxGetPr(G_PARAM(S));
    const real_T      *lpr     = mxGetPr(L_PARAM(S));
    const real_T      *dpr     = mxGetPr(D_PARAM(S));
    
    /* xdot=f(x,u) */
    /* x = [x,v,theta,omega] */
    /* States */
    omega = x[3], theta = x[2];
    /* Input */
    F = U(0);
    /* Parameters */
    //M = 1000.0; m = 0.1; g = 9.81; l = 0.5; d = 0.0;
    M = *Mpr; m = *mpr; g = *gpr; l = *lpr; d = *dpr;
    /* Differential Equation */
    //ssWarning(S,"Calculating Derivatives ... \n");
    dx[0] = x[1];
    dx[1] = (-cos(theta)*m*g*l*sin(theta)+sin(theta)*m*l*l*omega*omega+cos(theta)*d*omega+l*F)/((M+m*sin(theta)*sin(theta))*l);
    dx[2] = x[3];
    dx[3] = -(d*omega*M+d*omega*m-m*g*l*sin(theta)*M-m*m*g*l*sin(theta)+m*l*cos(theta)*F+m*m*l*l*cos(theta)*omega*omega*sin(theta))/((M+m*sin(theta)*sin(theta))*m*l*l);
}



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    No termination needed, but we are required to have this routine.
 */
static void mdlTerminate(SimStruct *S)
{
    UNUSED_ARG(S); /* unused input argument */
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
