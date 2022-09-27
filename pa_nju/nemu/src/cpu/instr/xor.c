#include "cpu/instr.h"
/*
Put the implementations of `xor' instructions here.
*/
make_instr_func(xor_3x)
{
    FUNCMAKER1(alu_xor)
}

make_instr_func(xor_grp1)
{
    FUNCMAKER2(alu_xor)
}