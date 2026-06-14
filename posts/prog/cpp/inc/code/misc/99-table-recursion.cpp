#include <stdio.h>
#include <stdlib.h>

void calcTable(int col, int row, int rewind = 1)
{
  if (col > 1 && rewind) {
    calcTable(col - 1, row, rewind);
    printf("\n");
  }

  if (row > 1) {
    calcTable(col, row - 1, 0);
  }

  printf("%dx%d=%2d  ", col, row, row * col);
}

int main (int argc, char *argv[])
{
  calcTable(9, 9);
  printf("\n");

  system("PAUSE");
  return 0;
}
