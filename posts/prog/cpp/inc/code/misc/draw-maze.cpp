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


class Maze {
 public:
  void draw();
};

void Maze::draw()
{
  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 12; b++) {
      if (map[a][b] == 1) {
        cout << "¡½";
      } else if (map[a][b] == 0) {
        cout << "  ";
      } else {
        cout << "¢I";
      }
    }

    cout<<endl;
  }
};

int main()
{
  Maze mouse;
  mouse.draw();
  cout << "done" << endl;

  system("pause");
  return 0;
}
