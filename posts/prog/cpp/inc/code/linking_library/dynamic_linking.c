#include "dep1.h"
#include "dep2.h"

__asm__(".symver show, show@API_1.0");
//__asm__(".symver show, show@API_1.1");
//__asm__(".symver sum, sum@API_1.0");


int main(void)
{
    show();
    sum(1, 2);

    return 0;
}
