#include <stdio.h>
#include "memp.h"

int main()
{
	char* p = NULL;

	mem_init();

	p = mem_malloc(1024);

	printf("free:%dKB\n", mem_getfree());
	printf("used:%dKB\n", mem_getused());

	mem_memcpy(p, "helloworld", 10);
	printf("p:%s\n", p);

	mem_free(p);

	printf("free:%dKB\n", mem_getfree());
	printf("used:%dKB\n", mem_getused());

	return 0;
}
