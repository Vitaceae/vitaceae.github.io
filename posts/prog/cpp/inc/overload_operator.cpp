/*------------------------------------------------------------------------------
 *  overload binary operator using member function
 *----------------------------------------------------------------------------*/

class MyOp {
 private:
  float val;

 public:
  MyOp(float x) : val(x) {}
  MyOp() : val(0) {}

  //'val' inside statements can be replaced with this->val
  //cannot use 'MyOp&' because it's a local object(reclaimed when leaving scope)
  MyOp operator + (const MyOp& F) const {return MyOp(val + F.val);}
  MyOp operator ^ (const float& f) const {return MyOp(pow(val, f));}

  //conversion operator
  operator float() {return val;}

  //left operand changes; no const at the end
  MyOp& operator += (const MyOp& F) {val += F.val; return *this;}
}

/*------------------------------------------------------------------------------
 *  overload binary operator using friend function
 *----------------------------------------------------------------------------*/

class MyOp {
  friend MyOp operator + (const MyOp& L, const MyOp& R);
  friend MyOp operator ^ (const MyOp& L, const MyOp& R);
  friend MyOp operator += (MyOp& L, const MyOp& R);

 private:
  float val;

 public:
  operator float() {return val;}
}

MyOp operator + (const MyOp& L, const MyOp& R) {return MyOp(L.val + R.val);}
MyOp operator ^ (const MyOp& L, const MyOp& R) {return MyOp(pow(L.val, R.val));}
MyOp& operator += (MyOp& L, const MyOp& R) {L.val += R.val; return L;}

/*------------------------------------------------------------------------------
 *  overload unary operator using member function
 *----------------------------------------------------------------------------*/

class MyOp {
 private:
  float val;

 public:
  MyOp(float x) : val(x) {}
  MyOp() : val(0) {}

  //prefix
  MyOp operator - () const {return MyOp(-val);}
  MyOp& operator ++ () {++val; return *this;}

  //postfix
  //int: dummy constnt value to distinguish from the prefix case
  //use copy constructor to save old value and return; increase the object value
  MyOp operator ++ (int) {MyOp temp(val); val++; return temp;}

  //conversion operator
  operator float() {return val;}
}

/*------------------------------------------------------------------------------
 *  overload unary operator using friend function
 *----------------------------------------------------------------------------*/

class MyOp {
  //prefix case
  friend MyOp operator ! (const MyOp& F1);
  friend MyOp& operator -- (MyOp& F1);

  //postfix case
  //dummy constnt value to distinguish from the prefix case
  friend MyOp& operator -- (MyOp& F1, int);

 private:
  float val;

  MyOp(float x) : val(x) {}
  MyOp() : val(0) {}
}

//prefix case
MyOp operator ! (const MyOp& F1) {return MyOp(F1.val * F1.val)}
MyOp& operator -- (MyOp& F1) {F1.val--; return F1;}
//postfix case
MyOp& operator -- (MyOp& F1, int) {MyOp temp(F1.val); F1.val--; return temp;}
