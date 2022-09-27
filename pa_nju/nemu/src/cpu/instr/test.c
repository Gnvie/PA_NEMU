#include "cpu/instr.h"
/*
Put the implementations of `test' instructions here.
*/
make_instr_func(test_85)
{
    OPERAND op1,op2;
    int len=1;
    GETEVGV
	alu_and(op1.val,op2.val,data_size);
    return len;
}

make_instr_func(test_84)
{
    OPERAND op1,op2;
    int len=1;
    GETEBGB
	alu_and(op1.val,op2.val,8);
    return len;
}

make_instr_func(test_f6_0)
{
    OPERAND op1,op2;
    int len=1;
    GETEBIB
	alu_and(op1.val,op2.val,8);
    return len;
}

make_instr_func(test_f7_0)
{
    OPERAND op1,op2;
    int len=1;
    GETEVIV
	alu_and(op1.val,op2.val,data_size);
    return len;
}

make_instr_func(test_a8)
{
    OPERAND op1,op2;
    int len=1;
    GETALIB
	alu_and(op1.val,op2.val,8);
    return len;
}

make_instr_func(test_a9)
{
    OPERAND op1,op2;
    int len=1;
    GETEAXIV
	alu_and(op1.val,op2.val,data_size);
    return len;
}