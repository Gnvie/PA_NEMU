#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/

make_instr_func(add_grp1)
{
    FUNCMAKER2(alu_add);
}

make_instr_func(add_0x)
{
    FUNCMAKER1(alu_add)
}
