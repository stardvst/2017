#include <iostream>
#include <vector>


class A {
public:
  A(int nn = 0) : n(nn) {}

  virtual int value() const { return n; }
  virtual ~A() {}
protected:
  int n;
};

class B : public A {
public:
  B(int nn = 0) : A(nn) {}
  virtual int value() const { return n + 1; }
};


int main() {

  const A a(1);
  const B b(3);
  const A* x[2] = { &a, &b }; 

  typedef std::vector<A> V; 
  V y;
  y.push_back(a);
  y.push_back(b);

  V::const_iterator i = y.begin();
  std::cout << x[0]->value(); 
  std::cout << x[1]->value(); // x is container of ptrs => B's value() is called
  std::cout << i->value();
  std::cout << (i + 1)->value(); // y is container of obs => A's value() is called

  std::cin.get();
  return 0;
}
