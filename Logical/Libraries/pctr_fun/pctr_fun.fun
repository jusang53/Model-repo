
FUNCTION_BLOCK pctrFub
	VAR_INPUT
		ssMethodType : SINT;
		ref : LREAL; (*Reference input*)
		x : ARRAY[0..3] OF LREAL; (*Inverted pendulum state x*)
		y : ARRAY[0..1] OF LREAL; (*Inverted pendulum output y*)
	END_VAR
	VAR_OUTPUT
		err_code : UINT; (*Controller error code*)
		F : LREAL; (*Car force*)
	END_VAR
	VAR
		bur_BlockIO_pend_ctrl_fun : BlockIO_pend_ctrl_fun;
		bur_D_Work_pend_ctrl_fun : D_Work_pend_ctrl_fun;
		bur_pend_ctrl_fun : tag_RTM_pend_ctrl_fun;
	END_VAR
END_FUNCTION_BLOCK
