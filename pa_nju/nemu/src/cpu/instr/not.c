#include "cpu/instr.h"
/*
Put the implementations of `not' instructions here.
*/
make_instr_func(not_f6_2)
{
    OPERAND op;
    int len=1;
    GETIMM(8)
    op.val=~op.val;
    operand_write(&op);
    return len;
}

make_instr_func(not_f7_2)
{
    OPERAND op;
    int len = 1;
    GETIM
    op.val=~op.val;
    operand_write(&op);
    return len;
}