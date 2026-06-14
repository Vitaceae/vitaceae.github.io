#include <iostream>
#include <iomanip>

using namespace std;

int map[10][12] =
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
int set[10][12];
int step[10][12];
int branch[10][12];

class Maze
{
private:

int tmp;
int presentpoint;
int branch_n,branch_s,branch_w,branch_e,branchcount,routecount,oldbranch;
int route_stack[100];
int branch_stack[100];

public:

Maze():branchcount(0),oldbranch(0),routecount(0),tmp(0){}
int  motion(void);
void searchway(void);
void route_push(int xr, int yr);
void branch_push(int xb, int yb);
int  route_pop(void);
int  branch_pop(void);
int  checkxy(int xi,int yi);
void popout(void);
};

int main()
{
Maze mouse;
char ch;
int x,y,p;

mouse.popout();
printf("\n");
cout<<"Enter Y/y to start:(others to leave)";
cin >> ch;

while(ch=='y' || ch=='Y')
  {
  for(x=0;x<10;x++)
    {for(y=0;y<12;y++)
       {
       set[x][y]=0;
       step[x][y]=-2;
       branch[x][y]=-1;
       }
    }
  cout<<"Enter the start point of row x and column y:"<<endl
      <<"row x:";    
  cin>>x;
  cout<<"row y:";
  cin>>y;
  
    if(mouse.checkxy(x-1,y-1))
      {
      if(mouse.motion())
        {mouse.popout();
         cout<<"==============No Exit!=============="<<endl;}
      else
        {mouse.popout();}
      }
    else
      {cout<<"======Invalid start point.======"<<endl;}

  cout<<"Enter Y/y to start:(others to leave)";
  cin >> ch;
  }

system("pause");
return 0;
}

int Maze::checkxy(int xi,int yi)
{
if(map[xi][yi]==0)
  {
   presentpoint=(100*xi+yi);
   step[xi][yi]=1;
   for(int i=0;i<100;i++)
     {route_stack[i]=-1;   branch_stack[i]=-2;}
   route_push(xi,yi);
   return 1;
  }
else
  {return 0;}
};

void Maze::searchway()
{
int y=(presentpoint%100),
    x=((presentpoint-y)/100);

for(int a=1;a<5;a++)
  {    
  switch(a)
    {
    case 1:
      if(map[x-1][y] != 1 && (x-1>=0) && (step[x][y]-1)!=step[x-1][y])
        {branch_n=1;}
    case 2:
      if(map[x+1][y] != 1 && (x+1<10) && (step[x][y]-1)!=step[x+1][y])
        {branch_s=1;}
    case 3:
      if(map[x][y-1] != 1 && (y-1)>=0 && (step[x][y]-1)!=step[x][y-1])
        {branch_w=1;}
    case 4:
      if(map[x][y+1] != 1 && (y+1)<12 && (step[x][y]-1)!=step[x][y+1])
        {branch_e=1;}
    }
  }
};

int Maze::motion()
{
int BRANCH;
do
  {
  int y=(presentpoint%100),
      x=((presentpoint-y)/100),
      s=0;
      
  branch_n=0; branch_s=0; branch_w=0; branch_e=0;
  searchway();
  BRANCH=(branch_n+branch_s+branch_w+branch_e);
    
  if(BRANCH>1 || branch[x][y]!=-1)
    {
    if(branch[x][y]==-1)
      {
      branch[x][y]=BRANCH-1;
      
      if((step[x-1][y]+1)==step[x][y]){set[x-1][y]=4;}
      if((step[x+1][y]+1)==step[x][y]){set[x+1][y]=4;}
      if((step[x][y-1]+1)==step[x][y]){set[x][y-1]=4;}
      if((step[x][y+1]+1)==step[x][y]){set[x][y+1]=4;}
      
      if(branch_w) {branch_push(x,y-1);} 
      if(branch_s) {branch_push(x+1,y);}
      if(branch_n) {branch_push(x-1,y);}
      if(branch_e) {branch_push(x,y+1);}
      
      s=step[x][y];
      presentpoint=branch_pop();
      y=(presentpoint%100);
      x=((presentpoint-y)/100);
      route_push(x,y);
      step[x][y]=s+1;
      }
    else if(branch[x][y]>0)
      {
      branch[x][y]--;
      s=step[x][y];
      set[x][y]=1;
      presentpoint=branch_pop();
      y=(presentpoint%100);
      x=((presentpoint-y)/100);
      route_push(x,y);
      step[x][y]=s+1;
      }
    else if(branch[x][y]==0)
      {if(branchcount==0)
         {return 1;}
       else
         {
         if(set[x-1][y]==4)
           {presentpoint=(100*(x-1)+y);
            route_push(x-1,y);
            step[x-1][y]=step[x][y]+1;}
         if(set[x+1][y]==4)
           {presentpoint=(100*(x+1)+y);
            route_push(x+1,y);
            step[x+1][y]=step[x][y]+1;}
         if(set[x][y-1]==4)
           {presentpoint=(100*x+(y-1));
            route_push(x,y-1);
            step[x][y-1]=step[x][y]+1;}
         if(set[x][y+1]==4)
           {presentpoint=(100*x+(y+1));
            route_push(x,y+1);
            step[x][y+1]=step[x][y]+1;}
         }
      } 
    }
  else if(BRANCH==1 && branch[x][y]==-1)
    {
    if(branch_n)
      {presentpoint=100*(x-1)+y;
       step[x-1][y]=step[x][y]+1;
       route_push(x-1,y);}
    if(branch_s)
      {presentpoint=100*(x+1)+y;
       step[x+1][y]=step[x][y]+1;
       route_push(x+1,y);}
    if(branch_w)
      {presentpoint=100*x+(y-1);
       step[x][y-1]=step[x][y]+1;
       route_push(x,y-1);}
    if(branch_e)
      {presentpoint=100*x+(y+1);
       step[x][y+1]=step[x][y]+1;
       route_push(x,y+1);}
    }
  else if(BRANCH==0)
    {
    if(branchcount!=0)
      {step[x][y]++;}
    else
      {return 1;}
    }
  }while(presentpoint!=411);

cout<<"================Win!================="<<endl;
return 0;
};

void Maze::route_push(int xr,int yr)
{*(route_stack+routecount)=(100*xr+yr);   routecount++;};
 
void Maze::branch_push(int xb,int yb)
{*(branch_stack+branchcount)=(100*xb+yb);   branchcount++;};

int Maze::route_pop()
{
routecount--;
tmp=*(route_stack+routecount);
*(route_stack+routecount)=-1;
return tmp;
};

int Maze::branch_pop()
{
branchcount--;
tmp=*(branch_stack+branchcount);
*(branch_stack+branchcount)=-2;
return tmp;
};

void Maze::popout()
{
for(int x=0;x<10;x++)
  {
   for(int y=0;y<12;y++)
     {
     if(map[x][y]==1)   {printf("¡½");}
     else 
       {
       if(step[x][y]>0)   {printf("¢I");}
       else   {printf("  ");}
       }
     if(x==4&&y==11){printf(" EXIT");}  
     if(x==7&&y==11){printf("\t¡½ : Wall");}
     if(x==8&&y==11){printf("\t¢I : Trace");}
     if(x==9&&y==11){printf("\t*  : Branch");}
     }
   printf("\n");
  }   

int i=0;        
branchcount=0;
while(routecount>0)
  {*(branch_stack+branchcount)=route_pop();   branchcount++;}  
while(branchcount>0)
  {
   if(i==4){cout<<endl;   i=0;}
   i++;
   tmp=branch_pop();
   if(set[(tmp-tmp%100)/100][tmp%100]!=1)   
     {cout<<"(x ="<<setw(2)<<(tmp-tmp%100)/100+1
          <<", y ="<<setw(2)<<tmp%100+1<<")  => ";}
   else
     {cout<<"(x ="<<setw(2)<<(tmp-tmp%100)/100+1
          <<", y ="<<setw(2)<<tmp%100+1<<") *=> ";}
   if(branchcount==0)
     {cout<<"(x ="<<setw(2)<<(tmp-tmp%100)/100+1
          <<", y ="<<setw(2)<<tmp%100+1<<")"<<endl;}
  }
};
