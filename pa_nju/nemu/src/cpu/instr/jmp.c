#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

// edited
        if(data_size==16)cpu.eip&=0xffff;
//
        return 1 + data_size / 8;
}

make_instr_func(jmp_eb)
{
    OPERAND op;
    int len=1;
    GETIMM(8)
    cpu.eip += sign_ext(op.val, 8);
    if(data_size==16)cpu.eip&=0xffff;
    return len;
}

make_instr_func(jmp_ff_4)
{
    OPERAND op;
    int len=1;
    GETIM
    cpu.eip = op.val;
    if(data_size==16)cpu.eip&=0xffff;
    return 0;
}

make_instr_func(jmp_ea)
{
    cpu.eip=instr_fetch(eip+1,data_size/8);
    cpu.cs.val=instr_fetch(eip+1+data_size/8,2);
    load_sreg(1);
    return 0;
}