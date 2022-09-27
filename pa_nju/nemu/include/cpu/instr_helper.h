#ifndef __INSTR_HELPER_H__
#define __INSTR_HELPER_H__

// the type of an instruction entry
typedef int (*instr_func)(uint32_t eip, uint8_t opcode);

void print_asm_0(char *instr, char *suffix, uint8_t len);
void print_asm_1(char *instr, char *suffix, uint8_t len, OPERAND *opr_1);
void print_asm_2(char *instr, char *suffix, uint8_t len, OPERAND *opr_1, OPERAND *opr_2);
void print_asm_3(char *instr, char *suffix, uint8_t len, OPERAND *opr_1, OPERAND *opr_2, OPERAND *opr_3);

// macro for making an instruction entry
#define make_instr_func(name) int name(uint32_t eip, uint8_t opcode)

// macro for generating the implementation of an instruction with one operand
#define make_instr_impl_1op(inst_name, src_type, suffix)                                                                        \
	make_instr_func(concat5(inst_name, _, src_type, _, suffix))                                                                 \
	{                                                                                                                           \
		int len = 1;                                                                                                            \
		concat(decode_data_size_, suffix)                                                                                       \
		concat3(decode_operand, _, src_type)                                                                                \
		print_asm_1(#inst_name, opr_src.data_size == 8 ? "b" : (opr_src.data_size == 16 ? "w" : "l"), len, &opr_src); \
		instr_execute_1op();                                                                                                    \
		return len;                                                                                                             \
	}

// macro for generating the implementation of an instruction with one operand and condition
// for jcc and setcc, the opcode type are always fixed so it will not appear in the function name
#define make_instr_impl_1op_cc(inst_name, src_type, suffix, cc) \
	make_instr_func(concat4(inst_name, cc, _, suffix))          \
	{                                                           \
		int len = 1;                                            \
		concat(decode_data_size_, suffix)                       \
		concat3(decode_operand, _, src_type)                \
		print_asm_1(#inst_name, #cc, len, &opr_src);    \
		if (concat(condition_, cc))                             \
			instr_execute_1op_cc_pass();                        \
		else                                                    \
			instr_execute_1op_cc_fail();                        \
		return len;                                             \
	}

// macro for generating the implementation of an instruction with two operands
#define make_instr_impl_2op(inst_name, src_type, dest_type, suffix)                                                                        \
	make_instr_func(concat7(inst_name, _, src_type, 2, dest_type, _, suffix))                                                              \
	{                                                                                                                                      \
		int len = 1;                                                                                                                       \
		concat(decode_data_size_, suffix)                                                                                                  \
		concat3(decode_operand, _, concat3(src_type, 2, dest_type))                                                                    \
		print_asm_2(#inst_name, opr_dest.data_size == 8 ? "b" : (opr_dest.data_size == 16 ? "w" : "l"), len, &opr_src, &opr_dest); \
		instr_execute_2op();                                                                                                               \
		return len;                                                                                                                        \
	}

// macro for generating the implementation of an instruction with two operands and condition
#define make_instr_impl_2op_cc(inst_name, src_type, dest_type, suffix, cc)                \
	make_instr_func(concat7(concat(inst_name, cc), _, src_type, 2, dest_type, _, suffix)) \
	{                                                                                     \
		int len = 1;                                                                      \
		concat(decode_data_size_, suffix)                                                 \
		concat3(decode_operand, _, concat3(src_type, 2, dest_type))                   \
		print_asm_2(#inst_name, #cc, len, &opr_src, &opr_dest);                   \
		if (concat(condition_, cc))                                                       \
			instr_execute_2op_cc_pass();                                                  \
		else                                                                              \
			instr_execute_2op_cc_fail();                                                  \
		return len;                                                                       \
	}

// determine the data size of operands
// possible sizes b, w, l, v, bv, short, near
#define decode_data_size_b opr_src.data_size = opr_dest.data_size = 8;
#define decode_data_size_w opr_src.data_size = opr_dest.data_size = 16;
#define decode_data_size_l opr_src.data_size = opr_dest.data_size = 32;
#define decode_data_size_v opr_src.data_size = opr_dest.data_size = data_size;
#define decode_data_size_bv \
	opr_src.data_size = 8;  \
	opr_dest.data_size = data_size;
#define decode_data_size_short_ opr_src.data_size = opr_dest.data_size = 8;
#define decode_data_size_near opr_src.data_size = opr_dest.data_size = 32;

// determine the type and address of operand(s)
// possible types: r, rm, i, m, a, c, o
// here c stands for CL, CX, or ECX

#define decode_operand_rm \
	len += modrm_rm(eip + 1, &opr_src);

#define decode_operand_r    \
	opr_src.type = OPR_REG; \
	opr_src.addr = opcode & 0x7;

// AL = AX = EAX
#define decode_operand_a    \
	opr_src.type = OPR_REG; \
	opr_src.addr = REG_AL;

#define decode_operand_i    \
	opr_src.type = OPR_IMM; \
	opr_src.sreg = SREG_CS; \
	opr_src.addr = eip + 1; \
	len += opr_src.data_size / 8;

#define decode_operand_r2rm \
	len += modrm_r_rm(eip + 1, &opr_src, &opr_dest);

#define decode_operand_rm2r \
	len += modrm_r_rm(eip + 1, &opr_dest, &opr_src);

#define decode_operand_i2rm              \
	len += modrm_rm(eip + 1, &opr_dest); \
	opr_src.type = OPR_IMM;              \
	opr_src.sreg = SREG_CS;              \
	opr_src.addr = eip + len;            \
	len += opr_src.data_size / 8;

#define decode_operand_i2r        \
	len += opr_src.data_size / 8; \
	opr_src.type = OPR_IMM;       \
	opr_src.sreg = SREG_CS;       \
	opr_src.addr = eip + 1;       \
	opr_dest.type = OPR_REG;      \
	opr_dest.addr = opcode & 0x7;

// REG_AL == REG_AX == REG_EAX == 0
#define decode_operand_i2a   \
	opr_src.type = OPR_IMM;  \
	opr_src.sreg = SREG_CS;  \
	opr_src.addr = eip + 1;  \
	opr_dest.type = OPR_REG; \
	opr_dest.addr = REG_AL;  \
	len += opr_src.data_size / 8;

// REG_CL == REG_CX == REG_ECX == 1
#define decode_operand_c2rm              \
	len += modrm_rm(eip + 1, &opr_dest); \
	opr_src.type = OPR_REG;              \
	opr_src.addr = REG_CL;

#define decode_operand_o2a                    \
	opr_src.type = OPR_MEM;                   \
	opr_src.sreg = SREG_DS;                   \
	if (verbose)                              \
		clear_operand_mem_addr(&opr_src);     \
	opr_src.addr = instr_fetch(eip + 1, 4);   \
	if (verbose)                              \
		opr_src.mem_addr.disp = opr_src.addr; \
	opr_dest.type = OPR_REG;                  \
	opr_dest.addr = REG_AL;                   \
	len += 4;

#define decode_operand_a2o                      \
	opr_dest.type = OPR_MEM;                    \
	opr_dest.sreg = SREG_DS;                    \
	if (verbose)                                \
		clear_operand_mem_addr(&opr_dest);      \
	opr_dest.addr = instr_fetch(eip + 1, 4);    \
	if (verbose)                                \
		opr_dest.mem_addr.disp = opr_dest.addr; \
	opr_src.type = OPR_REG;                     \
	opr_src.addr = REG_AL;                      \
	len += 4;

// conditions
// possible condition: e, a, ae, b, be, o, p, s , ne, na, no, np, ns, g, ge, l, le, ecxz

static inline bool inv_cc();

#define condition_e \
	cpu.eflags.ZF

#define condition_a \
	!(cpu.eflags.CF||cpu.eflags.ZF)

#define condition_ae \
	!cpu.eflags.CF

#define condition_b \
	cpu.eflags.CF

#define condition_be \
	cpu.eflags.CF||cpu.eflags.ZF

#define condition_o \
	cpu.eflags.OF

#define condition_p \
	cpu.eflags.CF

#define condition_s \
	cpu.eflags.SF

#define condition_ne \
	!cpu.eflags.ZF

#define condition_na \
	cpu.eflags.CF||cpu.eflags.ZF

#define condition_no \
	!cpu.eflags.OF

#define condition_np \
	!cpu.eflags.PF

#define condition_ns \
	!cpu.eflags.SF

#define condition_g \
	!(cpu.eflags.ZF||(cpu.eflags.SF^cpu.eflags.OF))

#define condition_ge \
	!(cpu.eflags.SF^cpu.eflags.OF)

#define condition_l \
	cpu.eflags.SF^cpu.eflags.OF

#define condition_le \
	cpu.eflags.ZF||(cpu.eflags.SF^cpu.eflags.OF)

#define condition_ecxz \
	cpu.ecx == 0

#define condition_c \
	cpu.eflags.CF

static inline bool inv_cc()
{
	printf("Please implement cc condition in instr_helper.h\n");
	fflush(stdout);
	assert(0);
	return false;
}

//edited below
#define PUSH \
    operand_read(&op);\
    cpu.esp-=data_size/8;\
    vaddr_write(cpu.esp,SREG_SS,data_size/8,op.val);\

#define POP \
    op.val=vaddr_read(cpu.esp,SREG_SS,data_size/8);\
    cpu.esp+=data_size/8;\
    operand_write(&op);\

#define GETEVGV \
    op1.data_size = data_size;\
    op2.data_size=data_size;\
    len+=modrm_r_rm(eip+1,&op1,&op2);\
    operand_read(&op1);\
    operand_read(&op2);\
    
    
#define GETEVIV \
    op1.data_size = data_size;\
    len+=modrm_rm(eip+1,&op1);\
    op2.type=OPR_IMM;\
    op2.data_size=data_size;\
    op2.addr=eip+len;\
    operand_read(&op1);\
    operand_read(&op2);\
    len+=data_size/8;\
    
#define GETEVIMM8 \
    op1.data_size = data_size;\
    len+=modrm_rm(eip+1,&op1);\
    op2.type=OPR_IMM;\
    op2.data_size=8;\
    op2.addr=eip+len;\
    operand_read(&op1);\
    operand_read(&op2);\
    len+=1;\
    
#define GETEAXIV \
    op1.data_size = data_size;\
    op1.type=OPR_REG;\
    op1.addr=0;\
    op2.data_size=data_size;\
    op2.addr=eip+1;\
    op2.type=OPR_IMM;\
    operand_read(&op1);\
    operand_read(&op2);\
    len+=data_size/8;\
    
#define GETEBGB \
    op1.data_size = 8;\
    op2.data_size=8;\
    len+=modrm_r_rm(eip+1,&op1,&op2);\
    operand_read(&op1);\
    operand_read(&op2);\
    
#define GETALIB \
    op1.data_size = 8;\
    op1.type=OPR_REG;\
    op1.addr=0;\
    op2.data_size=8;\
    op2.addr=eip+1;\
    op2.type=OPR_IMM;\
    operand_read(&op1);\
    operand_read(&op2);\
    len+=1;\
    
#define GETEBIB \
    op1.data_size = 8;\
    len+=modrm_rm(eip+1,&op1);\
    op2.type=OPR_IMM;\
    op2.data_size=8;\
    op2.addr=eip+len;\
    operand_read(&op1);\
    operand_read(&op2);\
    len+=1;\
    
#define GETIMM(length) \
    op.type = OPR_IMM;\
    op.data_size = length;\
    op.addr = eip + 1;\
    operand_read(&op);\
    len+=length/8;\
    
#define GETIM \
    op.data_size = data_size;\
    len+=modrm_rm(eip+1,&op);\
    operand_read(&op);\
    
    
#define FUNCMAKER1(opname) \
    OPERAND op1,op2;\
    int len=1;\
    switch(opcode&7)\
    {\
        case 0:\
            GETEBGB\
            op2.val=opname(op1.val,op2.val,8);\
            operand_write(&op2);\
            return len;\
        case 1:\
            GETEVGV\
            op2.val=opname(op1.val,op2.val,data_size);\
            operand_write(&op2);\
            return len;\
        case 2:\
            GETEBGB\
            op1.val=opname(op2.val,op1.val,8);\
            operand_write(&op1);\
            return len;\
        case 3:\
            GETEVGV\
            op1.val=opname(op2.val,op1.val,data_size);\
            operand_write(&op1);\
            return len;\
        case 4:\
            GETALIB\
            op1.val=opname(op2.val,op1.val,8);\
            operand_write(&op1);\
            return len;\
        case 5:\
            GETEAXIV\
            op1.val=opname(op2.val,op1.val,data_size);\
            operand_write(&op1);\
            return len;\
    }\
    return 0;\
    
#define FUNCMAKER2(opname) \
    OPERAND op1,op2;\
    int len=1;\
    int firstopcode=instr_fetch(eip, 1);\
    switch(firstopcode&3)\
    {\
        case 0:\
            GETEBIB\
            op1.val=opname(op2.val,op1.val,8);\
            operand_write(&op1);\
            return len;\
        case 1:\
            GETEVIV\
            op1.val=opname(op2.val,op1.val,data_size);\
            operand_write(&op1);\
            return len;\
        case 3:\
            GETEVIMM8\
            op1.val=opname(sign_ext(op2.val,op2.data_size),op1.val,data_size);\
            operand_write(&op1);\
            return len;\
    }\
    return 0;\

#endif
