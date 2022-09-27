#include "memory/mmu/cache.h"
#include<stdlib.h>
#include "memory/memory.h"

#define CACHE_LINE 1024
#define BIT_PER_LINE 64
uint8_t flag[CACHE_LINE];
uint32_t lineid[CACHE_LINE];
uint8_t cache[CACHE_LINE][BIT_PER_LINE];

// init the cache
void init_cache()
{
	memset(flag,0,sizeof(flag));
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
	if((paddr&63)+len>64)
    {
        uint32_t len1=64-(paddr&63);
        cache_write(paddr,len1,data&((1<<(len1*8))-1));
        cache_write(paddr+len1,len-len1,data>>(len1*8));
        return;
    }
	uint32_t place=paddr&63,groupid=(paddr>>6)&127,ptr=paddr>>13;
	memcpy(hw_mem + paddr, &data, len);
	for(int i=0;i<8;i++)
	{
	    uint32_t now=groupid*8+i;
	    if(lineid[now]==ptr&&flag[now])
	        memcpy(cache[now]+place,&data,len);
	}
	return;
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
    if((paddr&63)+len>64)
    {
        uint32_t len1=64-(paddr&63);
        return cache_read(paddr,len1)+(cache_read(paddr+len1,len-len1)<<(len1*8));
    }
    uint32_t rtn=0;
	uint32_t place=paddr&63,groupid=(paddr>>6)&127,ptr=paddr>>13;
	for(int i=0;i<8;i++)
	{
	    uint32_t now=groupid*8+i;
	    if(lineid[now]==ptr&&flag[now])
	    {
	        memcpy(&rtn,cache[now]+place,len);
	        return rtn;
	    }
	}
	uint8_t kill=rand()%8;
	uint32_t now=groupid*8+kill;
	memcpy(cache[now],hw_mem+(paddr>>6<<6),64);
	lineid[now]=ptr;
	flag[now]=1;
	memcpy(&rtn,cache[now]+place,len);
	return rtn;
}

