#include "cpu/instr.h"
/*
Put the implementations of `sbb' instructions here.
*/
make_instr_func(sbb_1x)
{
    FUNCMAKER1(alu_sbb);
}

make_instr_func(sbb_grp1)
{
    FUNCMAKER2(alu_sbb)
}