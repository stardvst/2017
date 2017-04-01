#include <iostream>


struct A {
  A() {}
  ~A() { std::cout << "dtor" << std::endl; }
};

int main() {

  A a;
  a.~A(); // ~A()

  std::cin.get();
  return 0;

  // ~A()
}
