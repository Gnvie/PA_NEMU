#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/
make_instr_func(lgdt)
{
    int len=1;
    OPERAND op;
    len+=modrm_rm(eip+1,&op);
    cpu.gdtr.base=vaddr_read(op.addr+2,op.sreg,4);
    cpu.gdtr.limit=vaddr_read(op.addr,op.sreg,2);
    if(data_size==16)cpu.gdtr.base&=0xffffff;
    return len;    
}
