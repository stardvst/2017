#include <iostream>


struct A {
  A(int xx) : x(xx) { 
    std::cout << x << std::endl; 
  }
  virtual ~A() {}
  int x;
};

struct B : virtual public A { B() : A(5) {} };
struct C : virtual public A { C() : A(0) {} };

struct D : public B, public C { D() : A(1) {} };


int main() {

  A* p = new D();
  delete p;

  std::cin.get();
  return 0;
}
