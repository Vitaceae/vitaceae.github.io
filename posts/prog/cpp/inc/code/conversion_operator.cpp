/**
 *  filename: conversion_operator.cpp
 */

#include <iostream>

using std::cout;
using std::endl;

class ConvOp
{
  private:
    int cust_int = 0;
    bool cust_bool = true;
  public:
    operator int() const {cout << "conv: return int" << endl; return cust_int;}
    explicit operator bool() const { cout << "conv: return bool" << endl; return cust_bool;}
};


int main()
{
  ConvOp conv;

  if (conv == 0) {
    cout << "conv is 0" << endl;
  }

  if (static_cast<bool>(conv) == true) {
    cout << "conv is true" << endl;
  }

  if (conv) {
    cout << "conv: no error" << endl;
  } else {
    cout << "conv: error" << endl;
  }

  return 0;
}