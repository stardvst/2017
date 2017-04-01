#include <iostream>


void f(int) { std::cout << "int" << std::endl; }
void f(unsigned short) { std::cout << "unsigned short" << std::endl; }
void f(unsigned int) { std::cout << "unsigned int" << std::endl; }


int main() {

  short c = 5;
  f(c);

  std::cin.get();
  return 0;
}
