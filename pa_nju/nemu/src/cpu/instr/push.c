#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/
make_instr_func(push_5x)
{
    OPERAND op;
    op.type=OPR_REG;
    op.data_size=data_size;
    op.addr=opcode&7;
    PUSH
    return 1;
}

make_instr_func(push_ff_6)
{
    OPERAND op;
    int len=1;
    op.data_size=data_size;
    len+=modrm_rm(eip+1,&op);
    PUSH
    return len;
}

make_instr_func(push_6a)
{
    OPERAND op;
    op.type=OPR_IMM;
    op.data_size=8;
    op.addr=eip+1;
    PUSH
    return 2;
}

make_instr_func(push_68)
{
    OPERAND op;
    op.type=OPR_IMM;
    op.data_size=data_size;
    op.addr=eip+1;
    PUSH
    return 1+data_size/8;
}

make_instr_func(pusha)
{
    if(data_size==16)
    {
        uint16_t tmp=cpu.esp;
        OPERAND op;
        op.type=OPR_REG;
        op.data_size=16;
        for(int i=0;i<8;i++)
        {
            if(i!=4)
            {
                op.addr=i;
                PUSH
            }
            else 
            {
                cpu.esp-=2;
                vaddr_write(cpu.esp,SREG_SS,2,tmp);
            }
        }
    }
    else
    {
        uint32_t tmp=cpu.esp;
        OPERAND op;
        op.type=OPR_REG;
        op.data_size=32;
        for(int i=0;i<8;i++)
        {
            if(i!=4)
            {
                op.addr=i;
                PUSH
            }
            else 
            {
                cpu.esp-=4;
                vaddr_write(cpu.esp,SREG_SS,4,tmp);
            }
        }
    }
    return 1;
}
