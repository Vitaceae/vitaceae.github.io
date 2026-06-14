#include <iostream>
#include <queue>
#include <stdlib.h>

using namespace std;

bool isop(char sign)
{
  if (sign == '+' || sign == '-' || sign == '*' || sign == '/') {
    return true;
  } else {
    return false;
  }
}

struct prefix
{
  int letter;
  int sign;
};

int main()
{
  prefix* ptr;
  char sign;
  queue<prefix> test, ans;

  cout << "Enter prefix expression to evaluate : " << endl << "Caution! : space is not allowed" << endl;

  while ((sign = cin.get()) != '\n') {
    if (!isop(sign)) {
      ptr = new prefix;
      int i = atoi(&sign);
      ptr->letter = i;
      ptr->sign = 0;
      ans.push(*ptr);
      delete ptr;
    } else {
      ptr = new prefix;
      ptr->letter = 0;

      switch (sign) {
      case '+':
        ptr->sign = 1;
        break;
      case '-':
        ptr->sign = 2;
        break;
      case '*':
        ptr->sign = 3;
        break;
      case '/':
        ptr->sign = 4;
        break;
      default:
        ptr->sign = 5;
        break;
      }

      ans.push(*ptr);
      delete ptr;
    }
  }

  prefix a, b, c;
  int match=0;

  while (ans.size() != 1) {
    while (ans.size() != 0) {
      if (test.size() == 0 || match == 1) {
        if (ans.size() >= 3) {
          a.letter = ans.front().letter;
          a.sign = ans.front().sign;
          ans.pop();

          b.letter = ans.front().letter;
          b.sign = ans.front().sign;
          ans.pop();

          c.letter = ans.front().letter;
          c.sign = ans.front().sign;
          ans.pop();

          match=0;
        } else {
          int count = ans.size();
          for(int k = 0; k < count; k++) {
            test.push(ans.front());
            ans.pop();
          }
        }
      } else {
        a.letter = b.letter;
        a.sign = b.sign;

        b.letter = c.letter;
        b.sign = c.sign;

        c.letter = ans.front().letter;
        c.sign = ans.front().sign;

        ans.pop();
      }

      int x = a.sign, y = b.sign, z = c.sign;

      if(x != 0 && y == 0 && z == 0) {
        int result;

        switch (x) {
        case 1:
          result = b.letter + c.letter;
          break;
        case 2:
          result = b.letter - c.letter;
          break;
        case 3:
          result = b.letter * c.letter;
          break;
        case 4:
          result = b.letter / c.letter;
          break;
        }

        prefix d;
        d.letter = result;
        d.sign = 0;
        test.push(d);
        match=1;
      } else {
        test.push(a);
      }
    }

    int tmp = test.size();

    for (int j = 0; j < tmp; j++) {
      prefix t;
      t.letter = test.front().letter;
      t.sign = test.front().sign;
      ans.push(t);
      test.pop();
    }
  }

  cout<<"Result : "<<ans.front().letter<<endl;
  system("pause");

  return 0;
}
