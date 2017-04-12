#include <iostream>
#include "prefix.hpp"


int main() {

  Prefix prefix("a.txt", "result.txt");

  try {
    prefix.evaluate();
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  std::cout << "see \"result.txt\" for the output" << std::endl;

  std::cin.get();
  return 0;
}
