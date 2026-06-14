#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

class Complex {
  friend void Show(const Complex&);
  friend inline float Abs (const Complex&);
  friend inline float Ang (const Complex&);
  friend inline float Real (const Complex&);
  friend inline float Imag (const Complex&);

  private:
    float *Z;

  public:
    Complex(float = 0.0, float = 0.0);
    Complex(const Complex&); //copy constructor
    ~Complex();

    Complex& operator = (const Complex&);
    inline Complex operator + (const Complex&);
    inline Complex operator * (const Complex&);
    Complex operator / (const Complex&);
    Complex operator || (const Complex &);
};

//destructor: reclaim dynamically allocated array
Complex::~Complex() {delete [] Z;}

//constructor
Complex::Complex(float x, float y)
{
  Z = new float [2];
  Z[0]=x;
  Z[1]=y;
}

//copy constructor
Complex::Complex(const Complex& OldZ)
{
  Z = new float [2];

  for (int i = 0; i < 2; i++) {
    Z[i]= OldZ.Z[i];
  }
}

//assignment operator '='
Complex& Complex::operator = (const Complex& Z2)
{
  for (int i=0; i<2; i++) {
    Z[i] = Z2.Z[i];
  }

  return *this;
}

Complex Complex::operator + (const Complex& Z2)
{
  return Complex(Z[0] + Z2.Z[0], Z[1] + Z2.Z[1]);
}

Complex Complex::operator * (const Complex& Z2)
{
  return Complex (Z[0] * Z2.Z[0] - Z[1] * Z2.Z[1],
                  Z[0] * Z2.Z[1] + Z[1] * Z2.Z[0]);
}

Complex Complex::operator / (const Complex& Z2)
{
  Complex Z1(Z[0], Z[1]);
  float r, im, Z1_r, Z1_im, Temp;

  r = Z2.Z[0];
  im = Z2.Z[1];
  Temp = r * r + im * im;
  Z1_r = Z1.Z[0];
  Z1_im = Z1.Z[1];

  return Complex((Z1_r * r + Z1_im * im) / Temp,
                 (Z1_im * r - Z1_r * im) / Temp);
}

Complex Complex::operator || (const Complex& Z2)
{
  Complex Z1(Z[0], Z[1]);

  return (Z1 * Z2) / (Z1 + Z2);
}

void Show(const Complex& Z1)
{
  float f, a;
  char Sign;

  f = Imag(Z1);
  if (f >= 0) {
    Sign = '+';
  } else {
    Sign = '-';
  }

  cout << setw(10) << setiosflags(ios::fixed) << setiosflags(ios::right)
       << setiosflags(ios::showpoint) << setprecision(5)
       << Z1.Z[0] << " " << Sign << " j " << fabs(f) << endl;
}

float Abs(const Complex& Z1) {return sqrt(Z1.Z[0] * Z1.Z[0] + Z1.Z[1] * Z1.Z[1]);}
float Ang(const Complex& Z1) {return atan2(Imag(Z1), Real(Z1));}
float Real(const Complex& Z1) {return Z1.Z[0];}
float Imag(const Complex& Z1) {return Z1.Z[1];}

void ShowPhasor(const Complex& Z1)
{
  float f, a;
  char Sign;

  cout << "Phasor:\n";
  cout << setw(10) << setiosflags(ios::fixed) << setiosflags(ios::right)
       << setiosflags(ios::showpoint) << setprecision(5)
       << Abs(Z1) << " phase " << Ang(Z1) << endl;
}

int main()
{
  float x1 = 3.5, y1 = 1.8;
  float x2 = 2.6, y2 = 7.2;
  Complex Z1(x1, y1);
  Complex Z2(x2, y2);
  Complex A;

  cout << "Z1   : "; Show(Z1);
  cout << "Z2   : "; Show(Z2);
  cout << "Z1+Z2: "; Show(Z1 + Z2);
  cout << "Z1*Z2: "; Show(Z1 * Z2);
  cout << "(1)  : "; Show(Z1 / Z2);
  cout << "(2)  : "; A = Z1 / Z2;
  cout << "(3)  : "; ShowPhasor(A);

  system("PAUSE");
  return 0;
}