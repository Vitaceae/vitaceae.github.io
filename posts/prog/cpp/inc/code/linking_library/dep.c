#include <stdio.h>

#include "dep.h"

//used version is less than v1.1
__asm__(".symver show_1_0, show@API_1.0");
//used by default if version is equal to or greater than v1.1
__asm__(".symver show_1_1, show@@API_1.1");


void show_1_0(void)
{
    printf("v1.0\n");
}

void show_1_1(void)
{
    printf("v1.1\n");
}

__asm__(".symver sum_1_0, sum@@API_1.0");
int sum_1_0(int a, int b)
{
    return a + b;
}

__asm__(".symver sub_1_1, sub@@API_1.1");
int sub_1_1(int a, int b)
{
    return a - b;
}

const api_t api = {
    .name = "dep",
    .show = show_1_1,
    .sum = sum_1_0,
    .sub = sub_1_1,
};
