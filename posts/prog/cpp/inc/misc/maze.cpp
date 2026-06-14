#include <iostream>

using namespace std;

int map[10][12] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
  {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
  {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int check[10][12];

class Maze {
 private:
  int flag;
  int x,y;
  int stack[100];
  int tmp;
  int msvalue;
  int msdirection;
  int direct;

 public:
  Maze() : tmp(0), flag(1), msvalue(1), msdirection(1) {}
  void popout();
  void mswork();
  int searchway(int x, int y);
  void push(int _x, int _y);
  int pop(void);
  void draw();
};

int stack1[100];
int tmp1;

void push1(int x, int y)
{
  stack1[tmp1] = x * 100 + y;
  tmp1++;
}

int pop1()
{
  tmp1--;
  return stack1[tmp1];
}

void Maze::popout()
{
  int b=tmp;

  for (int a = 0; a < b; a++) {
    int z = pop();
    y = z % 100;
    x = (z - y) / 100;
    push1(x, y);
  }

  for (int p = 0; p < b; p++) {
    int q = pop1();
    y = q % 100;
    x = (q - y) / 100;

    map[x][y] = 3;
    draw();
    cout << "<x =" << x << " " << "y =" << y << ">";
  }

  map[x][y] = 2;
  printf("%d", map[x][y]);
  draw();
  cout << "<x = 5 y = 12>" << "Arrive the Exit!!" << endl;
};

void Maze::mswork()
{
  cout << "1";
  x = 1;
  y = 1;

  do {
    direct = searchway(x, y);
    switch (direct) {
    case 1:
      if (map[x - 1][y] != 1 && (x - 1) >= 0) {
        push(x, y);
        check[x][y] = check[x][y] + flag;
        msvalue = check[x][y];
        flag++;
        x--;
      }
      break;
    case 2:
      if (map[x + 1][y] != 1 && (x + 1) < 10) {
        push(x, y);
        check[x][y] = check[x][y] + flag;
        msvalue = check[x][y];
        flag++;
        x++;
      }
      break;
    case 3:
      if (map[x][y - 1] != 1 && (y - 1) >= 0) {
        push(x, y);
        check[x][y] = check[x][y] + flag;
        msvalue = check[x][y];
        flag++;
        y--;
      }
      break;
    case 4:
      if(map[x][y + 1] != 1 && (y + 1) < 10) {
        push(x,y);
        check[x][y]=check[x][y]+flag;
        msvalue=check[x][y];
        flag++;
        y++;
      }
      break;
    }
  } while (!(x== 4 && y == 11));

  cout << "1.5";
  map[x][y] = 2;
};

int Maze::searchway(int x, int y)
{
  for (direct = 1; direct <= 4; direct++) {
    if (direct == 1 && map[x - 1][y] != 1 && (x - 1) > 0) {
      if (check[x - 1][y] <= msvalue) {
        msvalue = check[x - 1][y];
        msdirection = direct;
      }
    }

    if (direct == 2 && map[x + 1][y] != 1 && (x + 1) < 10) {
      if(check[x + 1][y] <= msvalue) {
        msvalue = check[x + 1][y];
        msdirection = direct;
      } else {
        break;
      }
    }

    if (direct == 3 && map[x][y - 1] != 1 && (y - 1) > 0) {
      if(check[x][y - 1] <= msvalue) {
        msvalue = check[x][y - 1];
        msdirection = direct;
      } else {
        break;
      }
    }

    if (direct == 4 && map[x][y + 1] != 1 && (y + 1) < 12) {
      if (check[x][y + 1] <= msvalue) {
        msvalue = check[x][y + 1];
        msdirection = direct;
      } else {
        break;
      }
    }
  }

  return msdirection;
};

void Maze::draw()
{
  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 12; b++) {
      if (map[a][b] == 1) {
          cout<<"¡½";
      } else if(map[a][b] == 0) {
          cout<<"  ";
      } else {
          cout<<"¢I";
      }
    }
    cout<<endl;
  }
};

void Maze::push(int _x, int _y)
{
  stack[tmp] = _x * 100 + _y;
  tmp++;
};

int Maze::pop(void)
{
  tmp--;
  return stack[tmp];
};

int main()
{
  Maze mouse;
  char ch;

  cout << "Enter Y/y to start the maze:(others to leave)";
  cin >> ch;

  while (!(ch == 'y' || ch == 'Y')) {
    getchar();
    return 0;
  }

  mouse.mswork();
  mouse.popout();
  getchar();
  system("pause");

  return 0;
}
