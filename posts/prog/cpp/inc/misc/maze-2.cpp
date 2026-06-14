#include <iostream>
#include        <stdio.h>
#include <conio.h> 
using namespace std;
char   map[10][12]=
{{1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,1,1,0,1,0,1,0,1},
{1,1,1,0,1,0,0,0,0,0,0,1},
{1,1,0,0,0,0,1,1,1,1,0,1},
{1,1,0,1,1,1,1,1,1,1,0,0},
{1,1,0,1,0,1,1,1,1,1,1,1},
{1,1,0,0,0,1,1,1,1,1,1,1},
{1,1,1,1,0,1,1,1,0,1,0,1},
{1,1,0,0,0,0,0,1,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1}};
typedef struct  A
{
int x;
int y;
}point;

char mark[10][12];
point   stack[1000];
int     top=-1;
void Push(point i)
{       if(top+1<1000)
{       stack[++top].x=i.x;
stack[  top].y=i.y;
}
else
{
printf("\nthe stack is full !\n");
exit(0);
}
}
point Pop()
{point   i;
if(top>-1)
{       i.x=stack[top  ].x;
i.y=stack[top--].y;
}
else
{
i.x=-1;
i.y=-1;
}
return i;
}
void ShowScreen()
{       int     i,j;
point   n;
clrscr();
for(i=0;i<10;i++)
printf("%s\n",map[i]);
for(i=0;i<=top;i++)
{       gotoxy(stack[i].y+1,stack[i].x+1);
putchar('0'+i%10);
delay(100);
}
printf("\nFind !!\n");
getch();
}
void Move(int x,int y)
{
point   i;
if(x==9 && y==11)
{       ShowScreen();
exit(0);
}
if(x+1<10 && mark[x+1][y]==' ' && map[x+1][y]==' ')
{       mark[x+1][y]='0';
i.x=x+1;
i.y=y;
Push(i);
Move(x+1,y);
Pop();
mark[x+1][y]=' ';
}
if(x-1>=0 && mark[x-1][y]==' ' && map[x-1][y]==' ')
{       mark[x-1][y]='0';
i.x=x-1;
i.y=y;
Push(i);
Move(x-1,y);
Pop();
mark[x-1][y]=' ';
}
if(y+1<12 && mark[x][y+1]==' ' && map[x][y+1]==' ')
{       mark[x][y+1]='0';
i.x=x;
i.y=y+1;
Push(i);
Move(x,y+1);
Pop();
mark[x][y+1]=' ';
}
if(y-1>=0 && mark[x][y-1]==' ' && map[x][y-1]==' ')
{       mark[x][y-1]='0';
i.x=x;
i.y=y-1;
Push(i);
Move(x,y-1);
Pop();
mark[x][y-1]=' ';
}
}
void main()
{
int     i,j;
point   start;
for(i=0;i<10;i++)
{       for(j=0;j<12;j++)
mark[i][j]=' ';
mark[i][j]=0;
}
for(i=0;i<10;i++)
{       for(j=0;j<12;j++)
map[i][j]=getchar();
getchar();
}
getch();
clrscr();
start.x=0;
start.y=0;
Push(start);
mark[start.x][start.y]='0';
Move(start.x, start.y);
}