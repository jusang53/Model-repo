/* Automation Studio generated header file */
/* Do not edit ! */
/* pctr_fun 1.00.0 */

#ifndef _PCTR_FUN_
#define _PCTR_FUN_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _pctr_fun_VERSION
#define _pctr_fun_VERSION 1.00.0
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Datatypes and datatypes of function blocks */
typedef struct BlockIO_pend_ctrl_fun
{	double Input;
	double Input_b[4];
	double Input1[2];
	double u;
	unsigned short err_code;
} BlockIO_pend_ctrl_fun;

typedef struct D_Work_pend_ctrl_fun
{	unsigned short local_err_code;
} D_Work_pend_ctrl_fun;

typedef struct tag_RTM_pend_ctrl_fun
{	unsigned char* errorStatus;
	struct BlockIO_pend_ctrl_fun* blockIO;
	struct D_Work_pend_ctrl_fun* dwork;
} tag_RTM_pend_ctrl_fun;

typedef struct pctrFub
{
	/* VAR_INPUT (analog) */
	signed char ssMethodType;
	double ref;
	double x[4];
	double y[2];
	/* VAR_OUTPUT (analog) */
	unsigned short err_code;
	double F;
	/* VAR (analog) */
	struct BlockIO_pend_ctrl_fun bur_BlockIO_pend_ctrl_fun;
	struct D_Work_pend_ctrl_fun bur_D_Work_pend_ctrl_fun;
	struct tag_RTM_pend_ctrl_fun bur_pend_ctrl_fun;
} pctrFub_typ;

typedef tag_RTM_pend_ctrl_fun RT_MODEL_pend_ctrl_fun;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void pctrFub(struct pctrFub* inst);


#ifdef __cplusplus
};
#endif
#endif /* _PCTR_FUN_ */

