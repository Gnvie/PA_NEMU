#include "cpu/instr.h"
/*
Put the implementations of `sub' instructions here.
*/
make_instr_func(sub_grp1)
{
    FUNCMAKER2(alu_sub)
}

make_instr_func(sub_2x)
{
    FUNCMAKER1(alu_sub)
}
