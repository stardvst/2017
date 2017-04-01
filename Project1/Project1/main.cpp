#include <iostream>
#include <algorithm>
#include <functional>


struct A {
  virtual void f() { std::cout << "A "; }
};

struct B : public A {
  virtual void f() { std::cout << "B "; }
};

int main() {

  A* a[] = { new A(), new B() };

  std::for_each(a, a + 2, std::mem_fun(&A::f));

  std::cin.get();
  return 0;
}
