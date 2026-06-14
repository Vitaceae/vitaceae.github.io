#include <iostream>
#include <stdio.h>
#include <stdbool.h>

using namespace std;

typedef struct Node {
  void* data;
  struct Node* link;
} StackNode;

typedef struct {
  int count;
  StackNode* top;
} StackStruct;

StackStruct* createStack(void)
{
  StackStruct* s = (StackStruct*)malloc(sizeof(StackStruct));

  if (s) {
    s->count = 0;
    s->top = NULL;
  }

  return s;
}

bool pushStack(StackStruct* stack, void* data)
{
  StackNode* node;

  node =(StackNode*)malloc(sizeof(StackNode));
  if (!node) {
    return false;
  }

  node->data = data;
  node->link = stack->top;
  stack->top = node;

  stack->count++;

  return true;
}

void* popStack(StackStruct* s)
{
  void* data;
  StackNode* temp;

  if (s->count == 0) {
    data = NULL;
  } else {
    temp = s->top;
    data = s->top->data;
    s->top = s->top->link;
    free(temp);
    s->count--;
  }

  return data;
}

bool emptyStack(StackStruct* s)
{
  return (s->count == 0);
}

int main()
{
  int x;
  StackStruct* s;
  char ch;

  s = createStack();

  cout << "Enter Y/y to read data:(others to leave)";
  cin >> ch;

  while (ch == 'y' || ch == 'Y') {
    cout << "input the data:";
    int* data = (int*)malloc(sizeof(int));
    cin >> x;
    *data=x;

    if (x > 0) {
      pushStack(s, data);
    }

    if (x <= 0) {
      cout << "popout:" << endl;
      for (int i = 0; i < 5; i++) {
        if (emptyStack(s) == 1) {
          cout << "ERROR!!" << endl;
          break;
        }

        if (emptyStack(s) == 0) {
          cout << *(int*)popStack(s) << endl;
        }
      }
    }

    cout << "Enter Y/y to read data:(others to leave)";
    cin >> ch;
  }

  system("pause");
  return 0;
}
