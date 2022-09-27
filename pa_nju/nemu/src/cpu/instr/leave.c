#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/
make_instr_func(leave)
{
    cpu.esp=cpu.ebp;
    OPERAND op;
    op.type=OPR_REG;
    op.data_size=data_size;
    op.addr=5;
    POP
    return 1;
}