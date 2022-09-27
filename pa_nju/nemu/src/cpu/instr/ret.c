#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_c3)
{
    if(data_size==16)
    {
        cpu.eip=vaddr_read(cpu.esp,SREG_SS,2);
        cpu.esp+=2;
    }
    else
    {
        cpu.eip=vaddr_read(cpu.esp,SREG_SS,4);
        cpu.esp+=4;
    }
    return 0;
}

make_instr_func(ret_c2)
{
    if(data_size==16)
    {
        cpu.eip=vaddr_read(cpu.esp,SREG_SS,2);
        cpu.esp+=2;
    }
    else
    {
        cpu.eip=vaddr_read(cpu.esp,SREG_SS,4);
        cpu.esp+=4;
    }
    OPERAND op;
    int len=1;
    GETIMM(16)
    cpu.esp+=op.val;
    return 0;
}
