#include <stdio.h>

int gcd(int a, int b)
{
    if (b == 0) {
        return a;
    }

    if (a == 0) {
        return b;
    }

    return gcd(b, a % b);
}

int main(void)
{
    int res, a, b;

    printf("Enter numbers to derive the GCD:\n");
    scanf(" %d", &a);
    scanf(" %d", &b);

    res = gcd(a, b);

    printf("GCD of %d & %d is %d\n", a, b, res);

    return 0;
}
