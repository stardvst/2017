#include <iostream>
#include <typeinfo>


int main() {

  int c = 1;
  c = ++c + ++c;
  std::cout << c;

  std::cin.get();
  return 0;
}
