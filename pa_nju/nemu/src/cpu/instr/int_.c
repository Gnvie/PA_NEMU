#include "cpu/intr.h"
#include "cpu/instr.h"

/*
Put the implementations of `int' instructions here.

Special note for `int': please use the instruction name `int_' instead of `int'.
*/
make_instr_func(int_cd)
{
    OPERAND op;
    int len=0;
    GETIMM(8)
    raise_sw_intr(op.val);
    return 0;
}
