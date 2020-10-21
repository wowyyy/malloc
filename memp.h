/*
 * malloc.h
 *
 *  Created on: 2019年11月26日
 *      Author: AnKun
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#ifndef NULL
#define NULL 0
#endif

#define MEM_BLOCK_SIZE		32                                      // 内存块大小
#define MEM_BLOCK_NUMS		1024                                    // 内存块数目
#define MEM_MAX_SIZE		(MEM_BLOCK_SIZE * MEM_BLOCK_NUMS)		// 内存池大小，32*1024=32KB

// 内存池初始化
void mem_init(void);

// 内存释放
void mem_free(void* p);

// 内存申请
void* mem_malloc(unsigned int size);

// 重新调整已有内存大小
void* mem_realloc(void* p, unsigned int size);

// 获得内存使用率
float mem_perused(void);

// 内存设置
void mem_memset(void* dst, unsigned char val, unsigned int size);

// 内存拷贝
void mem_memcpy(void* dst, const void* src, unsigned int size);

// 获得内存使用量
unsigned int mem_getused(void);

// 获得内存空余量
unsigned int mem_getfree(void);

// 获得内存大小
unsigned int mem_getsize(void);

#endif /* MALLOC_H_ */
