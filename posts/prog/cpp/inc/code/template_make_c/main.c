/**
 * main.c
 *
 * Author: Mike Chang
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/my_include.h"

void say_hi(void);

int main(void)
{
    printf("%s\n", MY_STRING);
    say_hi();

    return 0;
}
