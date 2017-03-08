#include <iostream>
#include <string>
#include "postfix.hpp"


int main() {

  std::string infix;
  std::cout << "enter infix expression: ";
  std::getline(std::cin, infix);

  std::string postfix = to_postfix(infix);
  std::cout << "\ncorresponding postfix expression is: " << postfix << "\n\n";

  evaluate(postfix);

  std::cin.get();
  return 0;
}
