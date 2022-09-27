#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_e8)
{
    OPERAND op;
    int len=1;
    GETIMM(data_size)
    if(data_size==16)
    {
        cpu.esp-=2;
        vaddr_write(cpu.esp,SREG_SS,2,cpu.eip+1+data_size/8);
        cpu.eip=(cpu.eip+op.val)&0xffff;
    }
    else
    {
        cpu.esp-=4;
        vaddr_write(cpu.esp,SREG_SS,4,cpu.eip+1+data_size/8);
        cpu.eip+=op.val;
    }
    return len;
}

make_instr_func(call_ff_2)
{
    OPERAND op;
    int len=1;
    op.data_size=data_size;
    len+=modrm_rm(eip+1,&op);
    operand_read(&op);
    if(data_size==16)
    {
        cpu.esp-=2;
        vaddr_write(cpu.esp,SREG_SS,2,cpu.eip+len);
        cpu.eip=op.val&0xffff;
    }
    else
    {
        cpu.esp-=4;
        vaddr_write(cpu.esp,SREG_SS,4,cpu.eip+len);
        cpu.eip=op.val;
    }
    return 0;
}
