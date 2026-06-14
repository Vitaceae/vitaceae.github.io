#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CONFIG_DEBUG_CALCULATION        1
#if CONFIG_DEBUG_CALCULATION == 1
#define debug(...)  printf(__VA_ARGS__);
#else
#define debug(...)
#endif

static unsigned int count(unsigned int t, unsigned int a, unsigned int b)
{
    unsigned int len = 1 << t;

    debug("t=%u, len=%u, b=%u\n", t, len, b);

    if (b > a) {
        return count(t, a, a) + count(t, a + 1, b);
    }

    if (!t) {
        debug("a%u calculation done\n", a);
        return 1;
    }

    if (b > len) {
        printf("invalid input: %d exceeds boundary\n", b);
        exit(-1);
    } else if (b > (len >> 1)) {
        return count(t - 1, a, b - (len >> 1));
    } else {
        debug("double!\n");
        return count(t - 1, a, b) << 1;
    }
}

int main(void)
{
    int ret;
    unsigned int a, b, t, sum;

    printf("t=");
    while ((ret = scanf("%u", &t)) && ret != 1) {;/*do nothing*/} 
    printf("a=");
    scanf("%u", &a);
    printf("b=");
    scanf("%u", &b);

    if (b > a) {
        sum = count(t, a, b);
    } else {
        sum = count(t, b, a);
    }
    printf("sum=%u\n", sum);

    return 0;
}
