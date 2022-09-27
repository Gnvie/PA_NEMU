#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	return offset+cpu.segReg[sreg].base;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	SegDesc ptr;
	ptr.val[0]=paddr_read(cpu.gdtr.base+cpu.segReg[sreg].index*8,4);
	ptr.val[1]=paddr_read(cpu.gdtr.base+cpu.segReg[sreg].index*8+4,4);
	cpu.segReg[sreg].base=(ptr.base_31_24<<24)+(ptr.base_23_16<<16)+ptr.base_15_0;
	cpu.segReg[sreg].limit=(ptr.limit_19_16<<16)+ptr.limit_15_0;
	assert(!cpu.segReg[sreg].base);
	assert(cpu.segReg[sreg].limit==0xfffff);
}
