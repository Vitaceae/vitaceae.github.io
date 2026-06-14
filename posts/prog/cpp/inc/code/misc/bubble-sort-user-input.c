#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *data, int n){
    int i, j, temp;

    for (i = n - 1; i > 0; i--) {
        for (j = 0; j <= i - 1; j++) {
            if (data[j] < data[j + 1]) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    int i, n, data[100] = {0};

    printf("Enter the numbers of data (less than 100): ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        printf("Enter the %dth data: ", i + 1);
        scanf("%d", &data[i]);
    }

    bubble_sort(data, n);

    printf("\nResult of the sort: ");
    for (i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }

    printf("\n");
    system("pause");
    return 0;
}
