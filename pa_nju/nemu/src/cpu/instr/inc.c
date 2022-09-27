#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
make_instr_func(inc_ff_0)
{
    OPERAND op;
    int len=1;
    op.data_size = data_size;
    len+=modrm_rm(eip+1,&op);
    
    operand_read(&op);
    int tmpcf=cpu.eflags.CF;
    op.val=alu_add(op.val,1,data_size);
    operand_write(&op);
    cpu.eflags.CF=tmpcf;
    return len;
}

make_instr_func(inc_4x)
{
    OPERAND op;
    op.type=OPR_REG;
    op.data_size = data_size;
    op.addr=opcode&7;
    
    operand_read(&op);
    int tmpcf=cpu.eflags.CF;
    op.val=alu_add(op.val,1,data_size);
    operand_write(&op);
    cpu.eflags.CF=tmpcf;
    return 1;
}