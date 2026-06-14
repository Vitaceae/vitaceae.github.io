// StringVector.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
  string A[] =
  {"John","Memi","Brigitte","Daiana","Lulu","Lisa"};
  vector<string>  S(A, A + 6);
  int i, Length=S.size();
  cout << "\nvector S 原來為: "  << endl;
  for (i = 0; i < Length; i++)
   cout << S[i] << "  ";
  cout << endl;
  // 插入
  S.insert(find(S.begin(), S.end(), "Daiana"), "Joanne");
  cout << "\n在 Daiana 前插入 Joanne" 
       << " 之後, vector S 為: "  << endl;
  for (i = 0; i < S.size(); i++)
   cout << S[i] << "  ";
  cout << endl;
  // 移除
  remove( S.begin(), S.end(), "Brigitte");
  S.resize(S.size()-1);
  cout << "\n在移除 Brigitte" 
       << " 之後, vector S 為: "  << endl;
  for (i = 0; i < Length; i++)
   cout << S[i] << "  ";
  cout << endl;

  // 取代
  *find(S.begin(), S.end(), "Daiana")= "William";
  cout << "\n將 Daiana 取代為 William" 
       << " 之後, vector S 為: "  << endl;
  for (i = 0; i < Length; i++)
   cout << S[i] << "  ";
  cout << endl;
  // 設定特定元素的值
  S.at(2) = "Peter";
  cout  << "\n在執行「S.at(2) = Peter」之後, S 變成為:"
        << endl;
  for (i = 0; i < Length; i++)
       cout << S[i] << "  ";
  cout << endl;
  // 插入額外的元素
  S.insert(S.begin() + 3, "Albert");
  cout  << "\n在執行「S.insert(S.begin() + 3, Albert)」"
        <<  "\n之後, S 變成為:"<< endl;
  for (i = 0; i < S.size(); i++)
       cout << S[i] << "  ";
  cout << endl;
  // 將 vector 物件各元素的值依大小排序
  //cout << endl;//**std::
  sort(S.begin(), S.end());
  cout << "\n排序之後, S 變成為:"
       << endl;
  for (i = 0; i < Length; i++)
   cout << S[i] << "  ";
  cout << endl;

  // 將 vector 物件各元素重新錯排 std::
  random_shuffle(S.begin(), S.end());
  cout << "\n重新錯排之後, S 變成為:"
       << endl;
  for (i = 0; i < Length; i++)
   cout << S[i] << "  ";
  cout << endl;

  system("pause");
  return 0;
}
