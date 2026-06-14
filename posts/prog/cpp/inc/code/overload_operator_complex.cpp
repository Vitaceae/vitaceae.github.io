/**
 *  filename: overload_operator_complex.cpp
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <locale>
#include <string>
#include <codecvt>

using namespace std;

class Complex {
  friend void show(const Complex&);
  friend inline float abs(const Complex&);
  friend inline float ang(const Complex&);
  friend inline float real(const Complex&);
  friend inline float imag(const Complex&);

 private:
  float *z;

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
Complex::~Complex() {delete [] z;}

//constructor
Complex::Complex(float x, float y)
{
  z = new float [2];
  z[0] = x;
  z[1] = y;
}

//copy constructor
Complex::Complex(const Complex& pre)
{
  z = new float [2];

  for (int i = 0; i < 2; i++) {
    z[i]= pre.z[i];
  }
}

//assignment operator '='
Complex& Complex::operator = (const Complex& op2)
{
  for (int i = 0; i < 2; i++) {
    z[i] = op2.z[i];
  }

  return *this;
}

Complex Complex::operator + (const Complex& op2)
{
  return Complex(z[0] + op2.z[0], z[1] + op2.z[1]);
}

Complex Complex::operator * (const Complex& op2)
{
  return Complex (z[0] * op2.z[0] - z[1] * op2.z[1], z[0] * op2.z[1] + z[1] * op2.z[0]);
}

//  (a + bi)   (a + bi)(c - di)   (ac + bd) + (bc - ad)i
//  -------- = ---------------- = ----------------------
//= (c + di)   (c + di)(c - di)        (c^2 + d^2)
Complex Complex::operator / (const Complex& op2)
{
  Complex op1(z[0], z[1]);
  float r1, i1, r2, i2, denominator;

  r2 = op2.z[0];
  i2 = op2.z[1];
  denominator = r2 * r2 + i2 * i2;
  r1 = op1.z[0];
  i1 = op1.z[1];

  return Complex((r1 * r2 + i1 * i2) / denominator, (i1 * r2 - r1 * i2) / denominator);
}

//parallel impedance
Complex Complex::operator || (const Complex& op2)
{
  Complex op1(z[0], z[1]);

  return (op1 * op2) / (op1 + op2);
}

void show(const Complex& op1)
{
  float f = imag(op1);
  char sign;

  sign = (f >= 0) ? '+' : '-';

  cout << setw(10) << setiosflags(ios::fixed) << setiosflags(ios::right)
       << setiosflags(ios::showpoint) << setprecision(5)
       << op1.z[0] << " " << sign << " j " << fabs(f) << endl;
}

float abs(const Complex& op1) {return sqrt(op1.z[0] * op1.z[0] + op1.z[1] * op1.z[1]);}
float ang(const Complex& op1) {return atan2(imag(op1), real(op1));}
float real(const Complex& op1) {return op1.z[0];}
float imag(const Complex& op1) {return op1.z[1];}


int main()
{
  float x1 = 3.5, y1 = 1.8;
  float x2 = 2.6, y2 = 7.2;
  Complex z1(x1, y1);
  Complex z2(x2, y2);
  Complex z3;

  cout << "-- calculate phasor --" << endl;
  cout << "z1     : "; show(z1);
  cout << "z2     : "; show(z2);
  cout << "z1 + z2: "; show(z1 + z2);
  cout << "z1 * z2: "; show(z1 * z2);
  cout << "z1 / z2: "; show(z1 / z2);
  z3 = z1 / z2;
  cout << "Phasor : " << setw(10) << setiosflags(ios::fixed | ios::right | ios::showpoint) << setprecision(5)
       << "magnitude=" << abs(z3) << ", phase(arg)=" << ang(z3) << endl;

  //impedance:
  //  omega = 2 * pi * freq
  //  C: capacitance
  //  L: inductance
  //             1                  1
  //  ZC = -------------- = -j -----------
  //       j * omega * C        omega * C
  //
  //  ZL = j * omega * L
  //
  //  ZR = R
  float omega = 1.0e4, C = 10e-6, L = 0.01;

  Complex ZC(0, -1 / (omega * C));
  Complex ZL(0, omega * L);
  Complex R1(100, 0);
  Complex R2(50, 0);
  Complex Zeq; //equivalent impedance

  /**
   * ──[R1]──[ZL]───┐
   *             ┌──┴──┐
   *           [R2]   [ZC]
   *             └──┬──┘
   * ───────────────┘
   */
  cout << "-- calculate impedance --" << endl;
  cout << "ZC     : "; show(ZC);
  cout << "ZL     : "; show(ZL);
  cout << "R1     : "; show(R1);
  cout << "R2     : "; show(R2);
  Zeq = (R1 + ZL) + (R2 || ZC);
  cout << "Zeq    : "; show(Zeq);
  cout << "Phasor : " << setw(10) << setiosflags(ios::fixed | ios::right | ios::showpoint) << setprecision(5)
       << "magnitude=" << abs(Zeq) << ", phase(arg)=" << ang(Zeq) << endl;

#ifdef _WIN32
  system("PAUSE");
#endif

  return 0;
}