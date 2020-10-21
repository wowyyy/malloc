/*
 * malloc.h
 *
 *  Created on: 2019��11��26��
 *      Author: AnKun
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#ifndef NULL
#define NULL 0
#endif

#define MEM_BLOCK_SIZE		32                                      // �ڴ���С
#define MEM_BLOCK_NUMS		1024                                    // �ڴ����Ŀ
#define MEM_MAX_SIZE		(MEM_BLOCK_SIZE * MEM_BLOCK_NUMS)		// �ڴ�ش�С��32*1024=32KB

// �ڴ�س�ʼ��
void mem_init(void);

// �ڴ��ͷ�
void mem_free(void* p);

// �ڴ�����
void* mem_malloc(unsigned int size);

// ���µ��������ڴ��С
void* mem_realloc(void* p, unsigned int size);

// ����ڴ�ʹ����
float mem_perused(void);

// �ڴ�����
void mem_memset(void* dst, unsigned char val, unsigned int size);

// �ڴ濽��
void mem_memcpy(void* dst, const void* src, unsigned int size);

// ����ڴ�ʹ����
unsigned int mem_getused(void);

// ����ڴ������
unsigned int mem_getfree(void);

// ����ڴ��С
unsigned int mem_getsize(void);

#endif /* MALLOC_H_ */
