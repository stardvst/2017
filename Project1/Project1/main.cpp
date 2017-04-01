#include <iostream>
#include <typeinfo>


int main() {

  int(*p)[10] = { 0 };

  std::cout << typeid(p).name() << std::endl;
  std::cout << (size_t)(p + 1) << std::endl;
  std::cout << (size_t)p << std::endl;

  std::cin.get();
  return 0;
}
