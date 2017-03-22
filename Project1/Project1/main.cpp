#include <exception>
#include <iostream>
#include "Virtual_memory.hpp"


int main() {

  Virtual_memory vm;

  int add1 = vm.allocate(20);
  int add2 = vm.allocate(10);
  int add3 = vm.allocate(5);
  int add4 = vm.allocate(8);
  int add5 = vm.allocate(15);

  try {
    vm.free(add2);
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  try {
    vm[add1] = 4;
    std::cout << static_cast<int>(vm[add1]) << '\n';
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  try {
    vm.free(add3);
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  try {
    vm[add3] = 5;
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  std::cout << "other available addresses: " << add4 << ", " << add5 << std::endl;

  std::cin.get();
  return 0;
}
