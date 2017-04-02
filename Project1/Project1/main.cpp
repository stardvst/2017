#include <iostream>


struct A {
  virtual int shift(int n = 2) const { return n << 2; }
};

struct B : A {
  int shift(int n = 3) const { return n << 3; }
};


int main() {

  const B b;
  const A* a = &b;

  std::cout << a->shift();

  std::cin.get();
  return 0;
}
