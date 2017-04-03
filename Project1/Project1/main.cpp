#include <iostream>


class A {
  int i;
  A() : i(0) { std::cout << "Hello world"; }
};


int main() {

  A a;

  std::cin.get();
  return 0;
}