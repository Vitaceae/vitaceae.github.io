#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
  int a[] = {20, 30, 40, 50};
  int b[] = {1, 3, 0, 2};
  int c[] = {0, 0, 0, 0};
  int length = sizeof(a) / sizeof(int);
  int temp = 0, j = 0, y = 0;

  for (int i = 0; i < length; i++) {
    c[i] = a[i];
    a[i] = b[i];
    b[i] = c[i];
  }

  //bubble sort: arranged in ascending order
  for (int x = 0; x <= length; x++) {
    for (y = x + 1; y <= length; y++) {
      if (a[x] > a[y]) {
        temp = a[y];
        a[y] = a[x];
        a[x] = temp;
      }
    }
  }

  //bubble sort: arranged in descending order
  for (int x = 0; x <= length; x++) {
    for (y = x + 1; y <= length; y++) {
      if(b[x] < b[y]) {
        temp = b[x];
        b[x] = b[y];
        b[y] = temp;
      }
    }
  }

  cout << "a=";
  for (int i = 0; i < length; i++) {
    cout << a[i];
    if (i != length - 1) {
      cout << ",";
    }
  }

  cout << endl << "b=" ;
  for (int i = 0; i < length; i++) {
    cout << b[i];
    if (i != length - 1) {
      cout << ",";
    }
  }
  cout << endl ;

  system("pause");
  return 0;
}
