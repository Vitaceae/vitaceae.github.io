#include <stdio.h>

long fib(long num)
{
    if(num == 0 || num == 1) {
        return num;
    }

    return fib(num - 1) + fib(num - 2);
}

int main(void)
{
    int sz = 0;

    printf("Enter the length of the Fibonacci series:\n");
    scanf(" %d", &sz);

    for (int i = 0; i < sz; i++) {
        if (i % 6) {
            printf(", %8ld", fib(i));
        } else {
            printf("\n%8ld", fib(i));
        }
    }

    printf("\n");
    return 0;
}

