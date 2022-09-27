#include "cpu/instr.h"
/*
Put the implementations of `and' instructions here.
*/
make_instr_func(and_grp1)
{
    FUNCMAKER2(alu_and)
}

make_instr_func(and_2x)
{
    FUNCMAKER1(alu_and)
}