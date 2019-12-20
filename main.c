#include <stdio.h>
#include "malloc.h"

int main()
{
	char* p = NULL;

	mem_init();			// 初始化内存池

	p = mem_malloc(1024);									// 申请内存
	printf("getused:%d\r\n", mem_getused());				// 获得内存使用量
	printf("perused:%.2f%%\r\n", mem_perused());			// 获得内存使用率

	mem_memcpy(p, "HelloWorld", 10);						// 内存拷贝
	printf("p:%s\r\n", p);									// 打印信息

	mem_free(p);											// 内存释放
	printf("perused:%.2f\r\n", mem_perused());			// 再次查看内存使用率

	return 0;
}
