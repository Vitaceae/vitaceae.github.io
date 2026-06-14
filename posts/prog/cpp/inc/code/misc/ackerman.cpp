#include <stdio.h>

int ackerman(int m,int n)
{
  if (m == 0) {
    return (n + 1);
  } else if (n == 0 && m > 0) {
    return ackerman((m - 1), 1);
  } else {
    return ackerman(m - 1, ackerman(m, n-1));
  }
};

int main(void)
{
  int m, n;

  printf("Enter m, n for Ackerman function:\n");
  scanf(" %d", &m);
  scanf(" %d", &n);

  printf("Ackerman output: %d\n", ackerman(m,n));

  return 0;
}
