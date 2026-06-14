#include <stdio.h>

double sqrt_root(double num, double ans, double tol)
{
    double x = ans * ans - num;

    if (x < 0) {
        x = -x;
    }

    if (x <= tol) {
        return ans;
    } else {
        return sqrt_root(num, (ans * ans + num) / (2 * ans), tol);
    }
}

int main(void)
{
    double num, ans, tol;

    printf("Enter a number which square root to be found: \n");
    scanf(" %lf",&num);

    ans = num - 1;
    tol = 0.000001;

    printf("The square root is: %lf\n", sqrt_root(num, ans, tol));

    return 0;
}
