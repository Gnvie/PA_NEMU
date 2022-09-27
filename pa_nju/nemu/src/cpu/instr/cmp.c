#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

make_instr_func(cmp_3x)
{
    OPERAND op1,op2;
    int len=1;
    switch(opcode&7)
    {
        case 0:
            GETEBGB
            alu_sub(op1.val,op2.val,8);
            return len;
        case 1:
            GETEVGV
            alu_sub(op1.val,op2.val,data_size);
            return len;
        case 2:
            GETEBGB
            alu_sub(op2.val,op1.val,8);
            return len;
        case 3:
            GETEVGV
            alu_sub(op2.val,op1.val,data_size);
            return len;
        case 4:
            GETALIB
            alu_sub(op2.val,op1.val,8);
            return len;
        case 5:
            GETEAXIV
            alu_sub(op2.val,op1.val,data_size);
            return len;
    }
    return 0;
}

make_instr_func(cmp_grp1)
{
    OPERAND op1,op2;
    int len=1;
    int firstopcode=instr_fetch(eip, 1);
    switch(firstopcode&3)
    {
        case 0:
            GETEBIB
            alu_sub(op2.val,op1.val,8);
            return len;
        case 1:
            GETEVIV
            alu_sub(op2.val,op1.val,data_size);
            return len;
        case 3:
            GETEVIMM8
            alu_sub(sign_ext(op2.val,op2.data_size),op1.val,data_size);
            return len;
    }
    return 0;
}