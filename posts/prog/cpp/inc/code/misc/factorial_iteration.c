#include <iostream>
#include <stdio.h>
#include <stdbool.h> 

//using namespace std;

int main()
{
    int i = 1, factN = 1, n;

    printf("Enter the number to be clculated:\n");
    scanf(" %d", &n);

    for (; i <= n; i++) {
        factN = factN * i;
    }
  
    printf("The factorial is: %d\n", factN);

    system("pause");  
    return 0;
}
