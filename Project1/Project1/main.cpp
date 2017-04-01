#include <iostream>


struct A {
  virtual void f(int x = 0) {
    std::cout << "A: " << x << std::endl;
  }
};

struct B : public A {
  virtual void f(int x = 1) {
    std::cout << "B: " << x << std::endl;
  }
};


int main() {

  A* p = new B();
  p->f();

  std::cin.get();
  return 0;
}
