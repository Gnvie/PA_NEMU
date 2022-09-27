#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/
make_instr_func(pop_5x)
{
    OPERAND op;
    op.type=OPR_REG;
    op.data_size=data_size;
    op.addr=opcode&7;
    POP
    return 1;
}

make_instr_func(popa)
{
    if(data_size==16)
    {
        OPERAND op;
        op.type=OPR_REG;
        op.data_size=16;
        for(int i=7;i>=0;i--)
        {
            if(i!=4)
            {
                op.addr=i;
                POP
            }
            else 
            {
                cpu.esp+=2;
            }
        }
    }
    else
    {
        OPERAND op;
        op.type=OPR_REG;
        op.data_size=32;
        for(int i=7;i>=0;i--)
        {
            if(i!=4)
            {
                op.addr=i;
                POP
            }
            else 
            {
                cpu.esp+=4;
            }
        }
    }
    return 1;
}
