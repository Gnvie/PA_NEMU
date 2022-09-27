#include "cpu/instr.h"
/*
Put the implementations of `dec' instructions here.
*/
make_instr_func(dec_4x)
{
    OPERAND op;
    op.type=OPR_REG;
    op.data_size=data_size;
    op.addr=opcode&7;
    operand_read(&op);
    int tmpcf=cpu.eflags.CF;
    op.val=alu_sub(1,op.val,data_size);
    operand_write(&op);
    cpu.eflags.CF=tmpcf;
    return 1;
}

make_instr_func(dec_ff_1)
{
    OPERAND op;
    int len=1;
    op.data_size = data_size;
    len+=modrm_rm(eip+1,&op);
    
    operand_read(&op);
    int tmpcf=cpu.eflags.CF;
    op.val=alu_sub(1,op.val,data_size);
    operand_write(&op);
    cpu.eflags.CF=tmpcf;
    return len;
}