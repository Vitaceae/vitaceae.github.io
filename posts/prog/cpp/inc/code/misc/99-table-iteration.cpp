#include <stdio.h>
#include <stdlib.h>

int main()
{
  for (int rewind = 3; rewind <= 9; rewind += 3) {
    for (int row = 1; row <= 9; row++) {
      for (int col = rewind - 2; col <= rewind; col++) {
        printf("%d x %d = %2d\t", col, row, row * col);
      }
      printf("\n");
    }
    printf("\n");
  }

  system("PAUSE");
  return 0;
}
