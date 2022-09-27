#include "cpu/instr.h"
/*
Put the implementations of `adc' instructions here.
*/
make_instr_func(adc_1x)
{
    FUNCMAKER1(alu_adc)
}

make_instr_func(adc_grp1)
{
    FUNCMAKER2(alu_adc)
}