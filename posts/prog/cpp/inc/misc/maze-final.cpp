#include <stdio.h>
#include <iostream>

using namespace std;

int maze[10][12] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
  {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 4},
  {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
  {1, 1, 0, 0, 0, 3, 0, 1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

constexpr std::uint_fast8_t wall{ 1 << 0 };
constexpr std::uint_fast8_t maze_exit{ 1 << 2 };
//constexpr std::uint_fast8_t traced{ 1 << 4 };
//std::uint_fast8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
//std::cout << "bit 0 is " << ((flags & mask0) ? "on\n" : "off\n");

const int path = 0;
//const int wall = 1;
const unsigned char traced = 0x10;
const int start = 3;
int exit_i = 4, exit_j = 11;
int success = 0;
int stack_i[100] = {0};
int stack_j[100] = {0};
int i_pointer = -1;
int j_pointer = -1;

bool markTraced(int i, int j)
{
  maze[i][j] |= traced;
}

bool isExit(int i, int j)
{
  return (maze[i][j] & maze_exit);
}

bool isPath(int i, int j)
{
  return (maze[i][j] == path || maze[i][j] == start || maze[i][j] == 4);
}

void run(int i,int j)
{
  if (isPath(i, j)) {
    markTraced(i, j);
    stack_i[++i_pointer] = i;
    stack_j[++j_pointer] = j;
  }

  if (i == exit_i && j == exit_j) {
    success = 1;
    return;
  }

  if (success != 1 && j <= 11 && isPath(i, j + 1)) {
    run(i, j + 1);
    return;
  }

  if (success != 1 && i <= 9 && isPath(i + 1, j)) {
    run(i + 1, j);
    return;
  }

  if (success != 1 && j >= 1 && isPath(i, j - 1)) {
    run(i, j - 1);
    return;
  }

  if (success != 1 && i >= 1 && isPath(i - 1, j)) {
    run(i - 1, j);
    return;
  }

  if (success != 1) {
    markTraced(i, j);
    i = stack_i[--i_pointer];
    j = stack_j[--j_pointer];
    run(i, j);
    return;
  }

//  cout << "< i=" << i << ", j=" << j << " >" << endl;
}

int main(void)
{
  char ch;

  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 12; b++) {
      if (maze[a][b] == start) {
        run(a, b);
      }
    }
  }

  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 12; b++) {
      if (maze[a][b] == start) {
        ch = 'S';
      } else if (a == exit_i && b == exit_j) {
        ch = 'D';
      } else if (maze[a][b] == 1) {
        //wall
        ch = 'X';
      } else if (maze[a][b] == 0) {
        //path
        ch = ' ';
      } else {
        //trace
        ch = '*';
      }

      cout << ch;
    }
    cout<<"\n";
  }

//  system("pause");
  return 0;
}
