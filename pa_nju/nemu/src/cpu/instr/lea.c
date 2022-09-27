#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/
make_instr_func(lea)
{
    int len = 1;
	OPERAND op1, op2;
	op1.data_size = data_size;
	op2.data_size = 32;
	len += modrm_r_rm(eip + 1, &op1, &op2);
	
	op1.val = op2.addr;
	operand_write(&op1);

	return len;
}