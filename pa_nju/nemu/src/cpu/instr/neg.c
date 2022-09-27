#include "cpu/instr.h"
/*
Put the implementations of `neg' instructions here.
*/
make_instr_func(neg_f6_3)
{
    OPERAND op;
    int len=1;
    GETIMM(8)
    cpu.eflags.CF=op.val!=0;
    op.val=-op.val;
    operand_write(&op);
    return len;
}

make_instr_func(neg_f7_3)
{
    OPERAND op;
    int len = 1;
    GETIM
    cpu.eflags.CF=op.val!=0;
    op.val=-op.val;
    operand_write(&op);
    return len;
}