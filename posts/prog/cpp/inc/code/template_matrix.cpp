#include <iostream>
#include <iomanip>
//#include <conio>

using namespace std;

inline void Check(bool ErrorCondition, const string& Message = "Requirement failed")
{
  if (ErrorCondition) {
    cerr << &Message << endl; exit(1);
  }
}

template <class T>
class Vector
{
  friend Vector<T> operator*(const T& , const Vector<T>& );    // Z3=f*Z2;
  friend Vector<T> operator*(const Vector<T>& , const T& );

 private:
  int Size;
  T* V;
  inline void Create(int);
 public:
  Vector(int);
  Vector(int, const T*);
  Vector(Vector<T>&);
  ~Vector();

  Vector<T> operator=(const Vector<T>&);
  Vector<T> operator+(const Vector<T>&);
  Vector<T> operator-(const Vector<T>&);
  T operator*(const Vector<T>&);
  Vector<T> operator/(const T&);
  T& operator[](int i)
    {
      Check(i>Size, "索引錯誤, 超過邊界!");
      return V[i];
    }

  void Display();
};

template <class T>
void Vector<T>::Create(int N)
{
  if (N < 1) {
    Size = 0;
    V = 0;
  } else {
    Size = N; V= new T[N+1];
  }
}

// 建構函數的定義
template <class T>
Vector<T>::Vector(int N)
{
  Create(N);
  return;
}

// 解構函數的定義
template <class T>
Vector<T>::~Vector()
  { delete [] V; }

// 複製建構函數的定義-1
template <class T>
Vector<T>::Vector(int N, const T* OldV)
{
  Create(N);
  for (int i=1; i<= Size; i++)
   V[i]= OldV[i-1];
  return;
}

// 複製建構函數的定義-2
template <class T>
Vector<T>::Vector(Vector<T>& OldV)
{
  Create(OldV.Size);
  for (int i=1; i<= Size; i++)
   V[i]= OldV.V[i];
  return;
}

// 定義指派運算子 operator = ()
template <class T>
Vector<T> Vector<T>::operator=(const Vector<T>& V2)
{
  if (Size!=V2.Size)
    Create(V2.Size);
  for (int i=1; i<= Size; i++)
       V[i] = V2.V[i];
  return *this;
}

// 定義加法運算子 operator + ()
template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& V2)
{
  Check(Size!=V2.Size,
     "加法運算錯誤, 長度不相同!");
  Vector<T> Temp(Size);
  for (int i=1; i<= Size; i++)
       Temp.V[i]= V[i]+V2.V[i];
  return Temp;
}

// 定義減法運算子 operator - ()
template <class T>
Vector<T> Vector<T>::operator-(const Vector<T>& V2)
{
  Check(Size!=V2.Size,
    "減法運算錯誤, 長度不相同!");
  Vector<T> Temp(Size);
  for (int i=1; i<= Size; i++)
       Temp.V[i]= V[i]-V2.V[i];
  return Temp;
}


// 定義乘法運算子-1  operator * ()
template <class T>
Vector<T> operator*(const T& f, const Vector<T>& V1)
{
     Vector<T> Temp(V1.Size);
     for(int i=1; i<=V1.Size; i++)
        Temp.V[i] = f * V1.V[i];
     return Temp;
}

// 定義乘法運算子-2  operator * ()
template <class T>
Vector<T> operator*(const Vector<T>& V1, const T& f)
{
     Vector<T> Temp(V1.Size);
     for(int i=1; i<=V1.Size; i++)
        Temp.V[i] = f * V1.V[i];
     return Temp;
}

// 定義乘法運算子-3 operator * ()
template <class T>
T Vector<T>::operator*(const Vector<T>& V2)
{
  Check(Size!=V2.Size,
        "內積運算錯誤, 長度不相同!");
  T Product = 0;
  for (int i=1; i<= Size; i++)
       Product += V[i]*V2.V[i];
  return Product;
}

// 定義成員函數 Display()
template <class T>
void Vector<T>::Display()
{
  for(int i = 1; i <= Size; i++)
    cout << setiosflags(ios::right)
         << setiosflags(ios::fixed)
         << setiosflags(ios::showpoint)
         << setprecision(4)
         << setw(12) << V[i];
    cout << endl;
  return;
}

// 定義除法運算子 operator / ()
template <class T>
Vector<T> Vector<T>::operator/(const T& f)
{
  Vector<T> Temp(Size);
  for (int i=1; i<= Size; i++)
       Temp.V[i]= V[i]/f;
  return Temp;
}

#endif

// Matrix.h

#ifndef Matrix_H
#define Matrix_H

#include <iostream>
#include <iomanip>
using namespace std;

// == 宣告 Matrix 樣版類別 ===============
template <class T>
class Matrix
{ 
  private:
    int M, N;
    T** A;
    void Create(int, int);
  public:
    // 宣告建構函數
    Matrix(int, int);
    Matrix(int, int, const T*);
    // 宣告複製建構函數
    Matrix(Matrix<T>&);
    // 宣告解構函數
    ~Matrix();
    //operator
    // 宣告指派運算子 operator = ()
    Matrix<T> operator=(const Matrix<T>&);
    // 宣告加法運算子 operator + ()
    Matrix<T> operator+(const Matrix<T>&);
    // 宣告乘法運算子 operator * ()
    Matrix<T> operator*(const Matrix<T>&);
    // 宣告索引運算子 operator [] ()
    T* operator[](int i){return A[i];}
    // 宣告成員函數 SetCol()
    void SetCol(int, Vector<T>&);
    // 宣告成員函數 PickCol()
    Vector<T> PickCol(int);
    // 宣告成員函數 Display()
    void Display();
};

// =======  成員函數的定義  ================
// 函數 Create() 的定義
template <class T>
void Matrix<T>::Create(int Row, int Col)
{
  Check((Row<1)||(Col<1),
    "矩陣建構錯誤, 行列大小不能為負值!");
  M = Row;
  N = Col;
  A = new T* [M+1];
  A[0]= new T[M*N+1];
  A[1]= A[0];
  for(int i=2; i<= M; i++)
     A[i]=A[i-1]+N;
}

// 建構函數的定義
template <class T>
Matrix<T>::Matrix(int Row, int Col)
   { Create(Row,Col);  return;}


// 建構函數的定義 (從一維陣列建立二維陣列)
template <class T>
Matrix<T>::Matrix(int Row, int Col, const T* V)
{ 
  Create(Row,Col);
  for(int i = 1; i <= M; i++)
    for(int j = 1; j <= N ; j++)
       A[i][j]=V[(i-1)*Col+(j-1)];
  return;
}

// 複製建構函數的定義
template <class T>
Matrix<T>::Matrix(Matrix<T>& OldM)
{ 
  Create(OldM.M, OldM.N);
  for(int i = 1; i <= M; i++)
    for(int j = 1; j <= N ; j++)
       A[i][j]=OldM.A[i][j];
  return;
}

// 解構函數的定義
template <class T>
Matrix<T>::~Matrix()
{ 
  delete [] A[0];
  delete [] A;
}

// 定義指派運算子 operator = ()
template <class T>
Matrix<T>
Matrix<T>::operator=(const Matrix<T>& M2)
{ 
  if ((M!=M2.M)||(N!=M2.N))
    Create(M2.M, M2.N);
  for(int i = 1; i <= M; i++)
    for(int j = 1; j <= N ; j++)
      A[i][j]=M2.A[i][j];
  return *this;
}

// 定義加法運算子 operator + ()
template <class T>
Matrix<T>
Matrix<T>::operator+(const Matrix<T>& M2)
{ 
  Check((M!=M2.M)||(N!=M2.N),
    "矩陣加法運算錯誤, 大小不相同!");
  Matrix<T> temp(M,N);
  for(int i = 1; i <= M; i++)
    for(int j = 1; j <= N ; j++)
           temp.A[i][j]=A[i][j]+M2.A[i][j];
  return temp;
}

// 定義乘法運算子  operator * ()
template <class T>
Matrix<T>
Matrix<T>::operator*(const Matrix<T>& M2)
{ 
  Check(N!=M2.M,
    "矩陣乘法運算錯誤, 大小不配!");
  Matrix<T> temp(M,M2.N);
  for(int i = 1; i <= M; i++)
    for(int j = 1; j <= M2.N ; j++)
      {	temp.A[i][j]=0.0;
        for(int k = 1; k <= N ; k++)
           temp.A[i][j]+=A[i][k]*M2.A[k][j];
      }
  return temp;
}

// 定義成員函數 Display()
template <class T>
void Matrix<T>::Display()
{   
    cout << setiosflags(ios::right)
         << setiosflags(ios::fixed)
         << setiosflags(ios::showpoint)
         << setprecision(4);
    for (int i = 1; i <= M; i++)
    { for(int j = 1; j <= N ; j++)
        cout << setw(10)
             << A[i][j] << " " ;
      cout << endl;
    }
    return;
}

// 定義成員函數 PickCol()
template <class T>
Vector<T> Matrix<T>::PickCol(int I)
{ 
  Vector<T> TempV(M);
  for (int i=1; i<= M; i++)
       TempV[i]= A[i][I];
  return TempV;
}

// 定義成員函數 SetCol()
template <class T>
void Matrix<T>::SetCol(int j, Vector<T>& V1)
{ 
  for (int i=1; i<= M; i++)
     A[i][j]= V1[i];
  return;
}

#endif

int main ()
{
	double W1[]={2.1, 0.5, 3.2, 6.4, 8.2, 4.9};
	double W2[]={4.6, 6.5, 3.6, 4.2, 5.8, 9.4};
	double W3[]={2.1, 3.2, 9.8, 6.9, 2.4, 1.6};
	double w1[]={2, 0.5};
	double w2[]={4, 6.5};
	Matrix<double> M1(2,3, W1);
	Matrix<double> M2(2,3, W2);
	Matrix<double> M3(3,2, W3);
	Matrix<double> Ma(2,3), Mb(2,2);
	Vector<double> V1(2, w1);
	Vector<double> V2(2, w2), Xa(3), Xb(3);

	cout << " M1 是:  "  << endl;
	M1.Display();
	cout << " M2 是:  "  << endl;
	M2.Display();
	cout << " M3 是:  "  << endl;
	M3.Display();
	Ma=M1+M2;
	cout << "(M1+M2) 是  :  "  << endl;
	Ma.Display();
	Mb=M1*M3;
	cout << "(M1*M3) 是  :  "  << endl;
	Mb.Display();
	V2 = M1.PickCol(2);
	cout << " M1 的第2行是:  " << endl;
	V2.Display();
	cout << " V1 是:  "  << endl;
	V1.Display();
	M1.SetCol(3,V1);
	cout << " 將 M1 的第3行設為 V1 後\n"
		<< " M1 變成為:  " << endl;
	M1.Display();
	system("pause");
	return 0;
}
