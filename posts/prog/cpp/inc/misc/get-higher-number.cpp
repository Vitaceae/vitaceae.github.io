#include <stdio.h>
#include <stdlib.h>

void* getLargerValue(void* data1, void* data2, int (*comp_func)(void*, void*))
{
  if ((*comp_func)(data1, data2) > 0) {
    return data1;
  } else {
    return data2;
  }
}

int compare(void* data1, void* data2)
{
  if (*(int*)data1 >= *(int*)data2) {
    return 1;
  } else {
    return -1;
  }
}

int main (void)
{
  int i = 7;
  int j = 8;
  int res;

  res = (*(int*)getLargerValue(&i, &j, compare));
  printf("larger value: %d\n", res);

  system("pause");
  return 0;
}
