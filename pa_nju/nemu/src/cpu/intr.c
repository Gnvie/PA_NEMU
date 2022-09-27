#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
    cpu.esp-=4;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eflags.val);
    cpu.esp-=2;
    vaddr_write(cpu.esp,SREG_SS,2,cpu.cs.val);
    cpu.esp-=4;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);
    uint32_t hi=laddr_read(cpu.idtr.base+8*intr_no+4,4),lo=laddr_read(cpu.idtr.base+8*intr_no,4);
    assert((hi>>8&31)==5||(hi>>8&31)==14||(hi>>8&31)==15);
    if((hi>>8&31)==14)cpu.eflags.IF=0;
    cpu.cs.val=lo>>16;
    cpu.eip=(hi>>16<<16)+(lo&0xffff);
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
