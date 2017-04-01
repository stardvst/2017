#include <iostream>


struct A {
  A(int xx) : x(0) {}
  int x;
};

struct B : virtual public A { B() : A(5) {} };
struct C : virtual public A { C() : A(0) {} };

struct D : public B, public C { D() : A(1) {} };


int main() {

  A arr[5];
  for(int i = 0; i < 3; ++i) {
    std::cout << arr[i].x;
  }

  std::cin.get();
  return 0;
}
