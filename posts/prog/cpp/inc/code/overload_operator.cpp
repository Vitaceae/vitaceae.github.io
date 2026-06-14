/**
 *  filename: overload_operator.cpp
 */

#include <iostream>
#include <cmath>

using namespace std;

class OverloadOp
{
 private:
  float operand;
 public:
  OverloadOp(float x) : operand(x) {}
  OverloadOp(): operand(0) {}
  //(implicit)conversion operator: convert all the output to float
  operator float() {return operand;}

  /* overload binary operators */
  //friend-function style overloading
  friend OverloadOp operator + (const OverloadOp& left, const OverloadOp& right);
  friend OverloadOp operator * (const OverloadOp& left, const OverloadOp& right);
  friend OverloadOp operator ^ (const OverloadOp& left, const OverloadOp& right);
  friend OverloadOp& operator += (OverloadOp& left, const OverloadOp& right);

  /* overload unary operators */
  //member-function style overloading
  //prefix
  OverloadOp operator - () const {return OverloadOp(-operand);}
  OverloadOp& operator ++ () {++operand; return *this;}
  //postfix
  //dummy constnt value to distinguish from the prefix case
  OverloadOp operator ++ (int) {OverloadOp post(operand); operand++; return post;}
  //friend-function style overloading
  friend OverloadOp operator ! (const OverloadOp& pre);
  //prefix
  friend OverloadOp& operator -- (OverloadOp& pre);
  //postfix
  //dummy constnt value to distinguish from the prefix case
  friend OverloadOp operator -- (OverloadOp& pre, int);
};

/* overload binary operators */
OverloadOp operator + (const OverloadOp& left, const OverloadOp& right) {return OverloadOp(left.operand + right.operand);}
OverloadOp operator * (const OverloadOp& left, const OverloadOp& right) {return OverloadOp(left.operand * right.operand);}
OverloadOp operator ^ (const OverloadOp& left, const OverloadOp& right) {return OverloadOp(pow(left.operand, right.operand));}
OverloadOp& operator += (OverloadOp& left, const OverloadOp& right) {left.operand += right.operand; return left;}

/* overload unary operators */
OverloadOp operator ! (const OverloadOp& pre) {return OverloadOp(pre.operand * pre.operand);}
OverloadOp& operator -- (OverloadOp& pre) {pre.operand--; return pre;}
OverloadOp operator -- (OverloadOp& pre, int) {OverloadOp post(pre.operand); pre.operand--; return post;}


int main(void)
{
  //initialize two operands d1 and d2
  OverloadOp left(2.4), right(3.5);

  cout << "-- overloading operators --" << endl;
  cout << "d1      : " << left << endl;
  cout << "d2      : " << right << endl;
  cout << "d1 + d2 : " << left + right << endl;
  cout << "d1 * d2 : " << left * right << endl;
  cout << "d1 ^ 2.5: " << (left ^ 2.5) << endl;
  cout << "d1 += d2: " << (left += right) << endl;

  cout << "-- overloading unary operators --" << endl;
  cout << "-d1     : " << (-left) << endl;
  cout << "!d1     : " << (!left) << endl;
  cout << "d1(before), ++d1, d1(after): " << left << ", " << (++left) << ", " << left << endl;
  cout << "d1(before), d1++, d1(after): " << left << ", " << (left++) << ", " << left << endl;
  cout << "d1(before), --d1, d1(after): " << left << ", " << (--left) << ", " << left << endl;
  cout << "d1(before), d1--, d1(after): " << left << ", " << (left--) << ", " << left << endl;

#ifdef _WIN32
  system("PAUSE");
#endif

  return 0;
}
