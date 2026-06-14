// StdVector.cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

// ------------- 主程式 ----------------------
int main()
{
	const int Size = 5;
	int i, SizeF, SizeC;
	float A[Size] = {1.5, 2.9, 3.8, 4.2, 5.7};
	char  B[Size] = {'b', 'a', 'i', 'r', 'w'};

	// 定義 vector 物件
	vector<float> Vf(A, A + Size);
	vector<char>  Vc(B, B + Size);
	SizeF=Vf.size();
	SizeC=Vc.size();
	// 定義 ostream 物件
	ostream_iterator<float> IntOut(cout, "  ");
	ostream_iterator<char>  CharOut(cout, "  ");
	cout << std::showpoint
		<< std::setprecision(4);
	cout << "\n-------測試 vector<float>-------------"
		<< endl;
	cout << "\nVf 為: "  << endl;
	// vector 物件的輸出
	for (i = 0; i < SizeF; i++)
		cout  << Vf[i] << "  ";
	// 設定特定元素的值
	Vf.at(2) = 9.9;
	cout << endl;
	cout << "在執行「Vf.at(2) = 9.9」之後, Vf 變成為:"
		<< endl;
	// vector 物件的輸出
	copy(Vf.begin(), Vf.end(), IntOut);
	cout << endl;
	Vf[3] = 2.8;
	cout << "在執行「Vf[3] = 2.8;」之後, Vf 變成為:"
		<< endl;
	copy(Vf.begin(), Vf.end(), IntOut);
	// 插入額外的元素
	Vf.insert(Vf.begin() + 3, 1.2);
	cout << "\n在執行「Vf.insert(Vf.begin() + 3, 1.2)」"
		<<  "\n之後, Vf 變成為:"<< endl;
	copy(Vf.begin(), Vf.end(), IntOut);
	// 將 vector 物件各元素的值依大小排序
	sort(Vf.begin(), Vf.end());
	cout << "\n排序之後, Vf 變成為:"     << endl;
	copy(Vf.begin(), Vf.end(), IntOut);
	// 將vector物件各元素重新錯排
	random_shuffle(Vf.begin(), Vf.end());
	cout << "\n重新錯排之後, Vf 變成為:(會與課本顯示不同)" << endl;
	// vector 物件的輸出
	copy(Vf.begin(), Vf.end(), IntOut);
	cout << endl;
	cout << "\n--------測試 vector<char>-----------------"
		<< endl;
	cout << "\nVc 為: "  << endl;
	// vector 物件的輸出
	for (i = 0; i < SizeC; i++)
		cout << Vc[i] << "  ";
	cout << endl;
	// 設定特定元素的值
	Vc.at(2) = 'h';
	cout << "在執行「Vc.at(2) = 'h'」之後, Vc 變成為:"
		<< endl;
	copy(Vc.begin(), Vc.end(), CharOut);
	cout << endl;
	Vc[3] = 'G';
	cout << "在執行「Vc[3] = 'G';」之後, Vf 變成為:"
		<< endl;
	copy(Vc.begin(), Vc.end(), CharOut);
	// 插入額外的元素
	Vc.insert(Vc.begin() + 3, 'p');
	cout << "在執行「Vc.insert(Vc.begin() + 3, 'p')」"
		<<  "\n之後, Vc 變成為:"<< endl;
	copy(Vc.begin(), Vc.end(), CharOut);
	// 將 vector 物件各元素的值依大小排序
	sort(Vc.begin(), Vc.end());
	cout << "\n排序之後, Vc 變成為:"
		<< endl;
	copy(Vc.begin(), Vc.end(), CharOut);
	// 將vector物件各元素重新錯排
	random_shuffle(Vc.begin(), Vc.end());
	cout << "\n重新錯排之後, Vc 變成為:"
		<< endl;
	copy(Vc.begin(), Vc.end(), CharOut);
	system("pause");
	return 0;
}

