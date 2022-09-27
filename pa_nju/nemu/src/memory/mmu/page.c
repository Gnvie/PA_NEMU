#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	uint32_t ptr=cpu.cr3.pdbr;
	PDE tmp1;
	tmp1.val=paddr_read((ptr<<12)+(laddr>>22)*4,4);
	assert(tmp1.present);
	ptr=tmp1.page_frame;
	PTE tmp2;
	tmp2.val=paddr_read((ptr<<12)+((laddr>>12)&0x3ff)*4,4);
	assert(tmp2.present);
	ptr=tmp2.page_frame;
	return (ptr<<12)+(laddr&0xfff);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
