#include <iostream>
#include "prefix.hpp"


int main() {

  Prefix prefix("prefix.txt", "result.txt");
  prefix.evaluate();

  std::cout << "see \"result.txt\" for the output" << std::endl;

  std::cin.get();
  return 0;
}
