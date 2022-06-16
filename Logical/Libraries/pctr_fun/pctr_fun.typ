

TYPE
	BlockIO_pend_ctrl_fun :  STRUCT   
		Input :  LREAL;   
		Input_b :  ARRAY[0..3] OF LREAL;   
		Input1 :  ARRAY[0..1] OF LREAL;   
		u :  LREAL;   
		err_code :  UINT;   
	END_STRUCT;

	D_Work_pend_ctrl_fun :  STRUCT   
		local_err_code :  UINT;   
	END_STRUCT;

	tag_RTM_pend_ctrl_fun :  STRUCT   
		errorStatus :  REFERENCE TO USINT;   
		blockIO :  REFERENCE TO BlockIO_pend_ctrl_fun;   
		dwork :  REFERENCE TO D_Work_pend_ctrl_fun;   
	END_STRUCT;

	RT_MODEL_pend_ctrl_fun :tag_RTM_pend_ctrl_fun;	(*  *)

END_TYPE
