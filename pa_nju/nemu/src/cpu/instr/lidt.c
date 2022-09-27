#include "cpu/instr.h"
/*
Put the implementations of `lidt' instructions here.
*/
make_instr_func(lidt)
{
    int len=1;
    OPERAND op;
    len+=modrm_rm(eip+1,&op);
    cpu.idtr.base=vaddr_read(op.addr+2,op.sreg,4);
    cpu.idtr.limit=vaddr_read(op.addr,op.sreg,2);
    if(data_size==16)cpu.idtr.base&=0xffffff;
    return len;    
}
