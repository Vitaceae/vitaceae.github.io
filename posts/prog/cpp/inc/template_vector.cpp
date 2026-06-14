#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

inline void Check(bool ErrorCondition, const string& Message = "Requirement failed")
{
  if (ErrorCondition) {
    cerr << Message << endl; exit(1);
  }
}

template <class T>
class Vector {
  friend Vector<T> operator * (const T&, const Vector<T>& ); // Z3=f*Z2;
  friend Vector<T> operator * (const Vector<T>&, const T& );

 private:
  int Size;
  T* V;
  inline void Create(int);

 public:
  Vector(int);
  Vector(int, const T*);
  Vector(Vector<T>&);
  ~Vector();

  Vector<T> operator = (const Vector<T>&);
  Vector<T> operator + (const Vector<T>&);
  Vector<T> operator - (const Vector<T>&);
  T operator * (const Vector<T>&);
  Vector<T> operator / (const T&);
  T& operator [] (int i)
    {
      Check(i>Size, "index overflow");
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
    Size = N;
    V = new T[N + 1];
  }
}

template <class T>
Vector<T>::Vector(int N) {Create(N);}

template <class T>
Vector<T>::~Vector() {delete [] V;}

template <class T>
Vector<T>::Vector(int N, const T* OldV)
{
  Create(N);

  for (int i=1; i<= Size; i++) {
    V[i] = OldV[i - 1];
  }
}

template <class T>
Vector<T>::Vector(Vector<T>& OldV)
{
  Create(OldV.Size);

  for (int i = 1; i <= Size; i++) {
    V[i] = OldV.V[i];
  }
}

template <class T>
Vector<T> Vector<T>::operator = (const Vector<T>& V2)
{
  if (Size != V2.Size) {
    Create(V2.Size);
  }

  for (int i = 1; i <= Size; i++) {
    V[i] = V2.V[i];
  }

  return *this;
}

template <class T>
Vector<T> Vector<T>::operator + (const Vector<T>& V2)
{
  Check(Size != V2.Size, "size mismatch");
  Vector<T> Temp(Size);

  for (int i = 1; i <= Size; i++) {
    Temp.V[i] = V[i] + V2.V[i];
  }

  return Temp;
}

template <class T>
Vector<T> Vector<T>::operator - (const Vector<T>& V2)
{
  Check(Size != V2.Size, "size mismatch");
  Vector<T> Temp(Size);

  for (int i = 1; i <= Size; i++) {
    Temp.V[i] = V[i] - V2.V[i];
  }

  return Temp;
}

template <class T>
Vector<T> operator * (const T& f, const Vector<T>& V1)
{
  Vector<T> Temp(V1.Size);

  for (int i = 1; i <= V1.Size; i++) {
    Temp.V[i] = f * V1.V[i];
  }

  return Temp;
}

template <class T>
Vector<T> operator * (const Vector<T>& V1, const T& f)
{
  Vector<T> Temp(V1.Size);

  for (int i = 1; i <= V1.Size; i++) {
    Temp.V[i] = f * V1.V[i];
  }

  return Temp;
}

template <class T>
T Vector<T>::operator * (const Vector<T>& V2)
{
  Check(Size!=V2.Size, "size mismatch");
  T Product = 0;

  for (int i = 1; i <= Size; i++) {
    Product += V[i] * V2.V[i];
  }

  return Product;
}

template <class T>
void Vector<T>::Display()
{
  for(int i = 1; i <= Size; i++) {
    cout << setiosflags(ios::right)
         << setiosflags(ios::fixed)
         << setiosflags(ios::showpoint)
         << setprecision(4)
         << setw(12) << V[i];
  }

  cout << endl;
}

template <class T>
Vector<T> Vector<T>::operator / (const T& f)
{
  Vector<T> Temp(Size);
  for (int i = 1; i <= Size; i++) {
    Temp.V[i] = V[i] / f;
  }

  return Temp;
}

int main()
{
  double Ddata1[] = {2, 0.5, 4.6};
  double Ddata2[] = {4, 6.5, 3.8};
  int Idata1[] = {2, 5, 6};
  int Idata2[] = {4, 65, 38};
  Vector<double> DV1(3, Ddata1);
  Vector<double> DV2(3, Ddata2), DVa(3), DVb(3);
  Vector<int> IV1(3, Idata1);
  Vector<int> IV2(3, Idata2), IVa(3), IVb(3);
  int Idot;
  double Ddot;

  cout << "\n---------------------" << endl;
  cout << "測試 Vector<double>:   " << endl;
  cout << " DV1 的值是:    "        << endl;
  DV1.Display();
  cout << " DV2 的值是:    "        << endl;
  DV2.Display();

  DVa = DV1 + DV2;
  cout << " (DV1 + DV2) 的值是:"    << endl;
  DVa.Display();

  DVb = DV1 / 2.0;
  cout << " (DV1/2.0)   的值是:  "    << endl;
  cout << "      "  << DVb[1]
       << "      "  << DVb[2]
       << "      "  << DVb[3]       << endl;
  Ddot = DV1 * DV2;
  cout << " DV1 和 DV2  的內積是 :    " << Ddot << endl;

  cout << "\n-------------------- " << endl;
  cout << "測試 Vector<int>: "      << endl;
  cout << " IV1 的值是: "           << endl;
  IV1.Display();
  cout << " IV2 的值是: "           << endl;
  IV2.Display();

  IVa = IV1 + IV2;
  cout << " (IV1 + IV2)的值是:"     << endl;
  IVa.Display();

  IVb = IV1 / 2.0;
  cout << " (IV1/2.0)  的值是:"     << endl;
  IVb.Display();

  Idot = IV1 * IV2;
  cout << " IV1 和 IV2 的內積是  :    " << Idot << endl;

  system("pause");

  return 0;
}
