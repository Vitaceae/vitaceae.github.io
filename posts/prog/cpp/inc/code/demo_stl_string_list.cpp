// StringList.cpp
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
  list<string>  S;
  list<string>::iterator Index;
  // 加入元素
  S.push_front("John");
  S.push_front("Memi");
  S.push_front("Brigitte");
  S.push_back("Daiana");
  S.push_back("Lulu");
  S.push_back("Lisa");
  
  cout << "\nlist S 原來為: "  << endl;
  for (Index = S.begin(); Index != S.end(); Index++)
        cout << *Index << "  ";
  cout << endl;
  // 插入
  S.insert(find(S.begin(), S.end(), "Daiana"), "Joanne");
  cout << "\n在 Daiana 前插入 Joanne" 
       << " 之後, list S 為: "  << endl;
  for (Index = S.begin(); Index != S.end(); Index++)
        cout << *Index << "  ";
  cout << endl;
  // 移除
  S.remove( "Brigitte");
  cout << "\n在移除 Brigitte" 
       << " 之後, list S 為: "  << endl;
  for (Index = S.begin(); Index != S.end(); Index++)
        cout << *Index << "  ";
  cout << endl;
  // 取代
  *find(S.begin(), S.end(), "Daiana")= "William";
  cout << "\n將 Daiana 取代為 William" 
       << " 之後, list S 為: "  << endl;
  for (Index = S.begin(); Index != S.end(); Index++)
        cout << *Index << "  ";
  cout << endl;
  // 將 list 物件各元素的值依大小排序
  S.sort();
  cout << "\n排序之後, S 變成為:"
       << endl;
  for (Index = S.begin(); Index != S.end(); Index++)
        cout << *Index << "  ";
  cout << endl;

  system("pause");
  return 0;
}
