#include <stdio.h>

int factorial(int n)
{
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    };
}

int main()
{
    int n;

    printf("Enter the number to be clculated:\n");
    scanf("%d", &n);

    printf("The factorial is: %d\n", factorial(n));

    return 0;
}
