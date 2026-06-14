#include <stdio.h>

#include "dep1.h"
#include "dep2.h"


//used version is less than v1.1
__asm__(".symver show_1_0, show@API_1.0");
//used by default if version is equal to or greater than v1.1
__asm__(".symver show_1_1, show@@API_1.1");


void show_1_0(void)
{
    dep2();
    printf("show(v1.0)\n");
}

void show_1_1(void)
{
    dep2();
    printf("show(v1.1)\n");
}

void sum(int a, int b)
{
    printf("sum(%d, %d)=%d\n", a, b, a + b);
}
