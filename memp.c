/*
 * malloc.c
 *
 *  Created on: 2019年11月26日
 *      Author: AnKun
 */


#include "memp.h"

__attribute__((aligned(4)))  unsigned char memory[MEM_MAX_SIZE];
__attribute__((aligned(4)))  unsigned short memtbl[MEM_BLOCK_NUMS];

/**
 * 内存拷贝函数
 * @param dst  目标地址
 * @param src  源地址
 * @param size 拷贝大小
 */
void mem_memcpy(void* dst, const void* src, unsigned int size)
{
	char* d = (char *)dst;
	const char* s = (char *)src;

	while (size >= sizeof(int))
	{
		*(int *)d = *(int *)s;
		d += sizeof(int);
		s += sizeof(int);
		size -= sizeof(int);
	}

	while (size--)
	{
		*d++ = *s++;
	}
}

/**
 * 内存设置函数
 * @param dst  目标地址
 * @param val  要设置的值
 * @param size 内存连续设置的长度
 */
void mem_memset(void* dst, unsigned char val, unsigned int size)
{
	unsigned int value = 0;
	unsigned char* p = (unsigned char *)dst;

	value =  (val << 24) | (val << 16) | (val << 8) | val;

	while (size >= sizeof(int))
	{
		*(unsigned int *)p = value;
		p += sizeof(int);
		size -= sizeof(int);
	}

	while (size--)
	{
		*p++ = val;
	}
}

/**
 * 内存申请函数,申请的内存空间会被初始化为0
 * @param size 要申请的大小
 * @return     申请成功返回内存地址，失败返回NULL
 */
void* mem_malloc(unsigned int size)
{
	int i = 0, k = 0;
	unsigned int nblocks = 0, cblocks = 0;
	unsigned char* p = NULL;

	if (!size)  return NULL;

	nblocks = (size - 1) / MEM_BLOCK_SIZE + 1;

	for (i = 0; i != MEM_BLOCK_NUMS; i++)
	{
		cblocks = memtbl[i] == 0 ? (cblocks + 1) : 0;
		if (cblocks == nblocks)
		{
			for (k = 0; k != nblocks; k++)
			{
				memtbl[i - k] = nblocks;
			}
			p = (unsigned char *)(memory + (i + 1 - nblocks) * MEM_BLOCK_SIZE);
			mem_memset(p, 0, nblocks * MEM_BLOCK_SIZE);
			return (void *)p;
		}
	}
	return NULL;
}

/**
 * 重新申请内存空间
 * @param p     旧地址
 * @param size  重新申请的大小
 * @return      新地址
 */
void* mem_realloc(void* p, unsigned int newSize)
{
	unsigned int index;
	unsigned int oldSize;
	unsigned char* newAddr = NULL;

	if (!p)  return mem_malloc(newSize);

	index = (((unsigned int)p) - ((unsigned int)memory)) / MEM_BLOCK_SIZE;
	oldSize = memtbl[index] * MEM_BLOCK_SIZE;

	if ((newAddr = mem_malloc(oldSize)) != NULL)
	{
		mem_memcpy(newAddr, p, newSize > oldSize ? oldSize : newSize);
		mem_free(p);
		return (void *)newAddr;
	}
	return NULL;
}

/**
 * 内存释放函数
 * @param p 要释放的内存地址
 */
void mem_free(void* p)
{
	int i;
	unsigned int index;
	unsigned int nblocks;

	if (!p) return;
	if (((unsigned int)p) < ((unsigned int)memory) || ((unsigned int)p) > ((unsigned int)(memory + MEM_MAX_SIZE - 1)))  return;

	index = (((unsigned int)p) - ((unsigned int)memory)) / MEM_BLOCK_SIZE;
	nblocks = memtbl[index];
	for (i = 0; i != nblocks; i++)
	{
		memtbl[index + i] = 0;
	}
}

/**
 * 获得内存使用率
 */
float mem_perused(void)
{
	unsigned int i = 0;
	unsigned int used = 0;
	for (i = 0; i != MEM_BLOCK_NUMS; i++)
	{
		if (memtbl[i] != 0)  used++;
	}
	return (((float)(used * 100)) / ((float)MEM_BLOCK_NUMS));
}

/**
 * 获得内存使用量
 */
unsigned int mem_getused(void)
{
	unsigned int i = 0;
	unsigned int used = 0;
	for (i = 0; i != MEM_BLOCK_NUMS; i++)
	{
		if (memtbl[i] != 0)  used++;
	}
	return used * MEM_BLOCK_SIZE;
}

/**
 * 获得内存空余量
 */
unsigned int mem_getfree(void)
{
	unsigned int i = 0;
	unsigned int free = 0;
	for (i = 0; i != MEM_BLOCK_NUMS; i++)
	{
		if (!memtbl[i])  free++;
	}
	return free * MEM_BLOCK_SIZE;
}

/**
 * 获得内存池总大小
 */
unsigned int mem_getsize(void)
{
	return sizeof(memory);
}

/**
 * 内存池初始化函数
 */
void mem_init(void)
{
	mem_memset(memory, 0, sizeof(memory));			// 初始化内存池
	mem_memset(memtbl, 0, sizeof(memtbl));			// 初始化内存索引表
}
