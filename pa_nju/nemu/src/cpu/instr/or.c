#include "cpu/instr.h"
/*
Put the implementations of `or' instructions here.
*/
make_instr_func(or_0x)
{
    FUNCMAKER1(alu_or)
}

make_instr_func(or_grp1)
{
    FUNCMAKER2(alu_or)
}