#include "cpu/cpu.h"


uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
    src&=MASK;
    dest&=MASK;
    uint32_t res=(src+dest)&MASK;
    cpu.eflags.CF=res<src;
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	cpu.eflags.OF=(getsign(src,data_size)==getsign(dest,data_size)&&getsign(src,data_size)!=getsign(res,data_size));
	return res;
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	if(!cpu.eflags.CF)return alu_add(src,dest,data_size);
	src&=MASK;
    dest&=MASK;
    uint32_t res=(src+dest+1)&MASK;
    cpu.eflags.CF=res<=src;
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	cpu.eflags.OF=(getsign(src,data_size)==getsign(dest,data_size)&&getsign(src,data_size)!=getsign(res,data_size));
	return res;
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	src&=MASK;
    dest&=MASK;
    uint32_t res=(dest-src)&MASK;
    cpu.eflags.CF=dest<src;
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	cpu.eflags.OF=(getsign(src,data_size)!=getsign(dest,data_size)&&getsign(dest,data_size)!=getsign(res,data_size));
	return res;
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
    if(!cpu.eflags.CF)return alu_sub(src,dest,data_size);
	src&=MASK;
    dest&=MASK;
    uint32_t res=(dest-src-1)&MASK;
    cpu.eflags.CF=dest<=src;
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	cpu.eflags.OF=(getsign(src,data_size)!=getsign(dest,data_size)&&getsign(dest,data_size)!=getsign(res,data_size));
	return res;
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	src&=MASK;
    dest&=MASK;
    uint64_t res=1ll*dest*src;
    cpu.eflags.CF=cpu.eflags.OF=((res&MASK)!=res);
	return res;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
    src&=MASK;
    dest&=MASK;
    src=sign_ext_64(src,data_size);
    dest=sign_ext_64(dest,data_size);
	return 1ll*src*dest;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	src&=MASK;
    uint64_t res=dest/src;
    assert(res<=MASK);
	return res;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	return dest/src;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
    return dest%src;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	return dest%src;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	src&=MASK;
    dest&=MASK;
    uint32_t res=dest&src;
    cpu.eflags.CF=0;
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	cpu.eflags.OF=0;
	return res;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	src&=MASK;
    dest&=MASK;
    uint32_t res=dest^src;
    cpu.eflags.CF=0;
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	cpu.eflags.OF=0;
	return res;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	src&=MASK;
    dest&=MASK;
    uint32_t res=dest|src;
    cpu.eflags.CF=0;
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	cpu.eflags.OF=0;
	return res;
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	src&=31;
    dest&=MASK;
    uint32_t res=(dest<<src)&MASK;
    cpu.eflags.CF=(src&&getsign(dest<<(src-1),data_size));
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	return res;
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	src&=31;
    dest&=MASK;
    uint32_t res=dest>>src;
    cpu.eflags.CF=(src&&(dest>>(src-1)&1));
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	return res;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	if(!getsign(dest,data_size))return alu_shr(src,dest,data_size);
	src&=31;
    dest&=MASK;
    uint32_t res=((dest^MASK)>>src)^MASK;
    cpu.eflags.CF=(src&&((((dest^MASK)>>(src-1))^MASK)&1));
    cpu.eflags.PF=!__builtin_parity(0xFF&res);
	cpu.eflags.ZF=res==0;
	cpu.eflags.SF=getsign(res,data_size);
	return res;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	return alu_shl(src,dest,data_size);
#endif
}
