#include <stdio.h>

int main()
{
    int num;
    long pre1 = 0, pre2 = 1, now;

    printf("Enter the number of the series to be displayed\n");
    scanf(" %ld", &num);

    printf("The series is: \n");

    for (int i = 0; i < num; i++) {
        if (i == 0) {
            printf("%10ld,",pre1);
        } else if(i==1) {
            printf("%10ld,",pre2);
        } else {
            now = pre1 + pre2;
            pre1 = pre2;
            pre2 = now;
            if(!(i % 7)) {
                printf("\n%10ld,", now);
            } else {
                printf("%10ld,", now);
            }
        }
    }

    return 0;
}

/**
 * result:
 *  Enter the number of the series to be displayed
 *  42
 *  The series is:
 *           1,         1,         2,         3,         5,         8,        13,
 *          21,        34,        55,        89,       144,       233,       377,
 *         610,       987,      1597,      2584,      4181,      6765,     10946,
 *       17711,     28657,     46368,     75025,    121393,    196418,    317811,
 *      514229,    832040,   1346269,   2178309,   3524578,   5702887,   9227465,
 *    14930352,  24157817,  39088169,  63245986, 102334155, 165580141, 267914296,
 */