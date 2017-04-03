#include <iostream>


int& foo() {
  static int a = 3;
  return a;
}


int main() {

  ++++foo();
  std::cout << foo();

  std::cin.get();
  return 0;
}