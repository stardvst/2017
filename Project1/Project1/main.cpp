#include <iostream>
#include "expression.hpp"
#include "balanced.hpp"


int main() {

  Expression expr("(");

  while(!balanced(expr)) {
    std::cout << "enter a valid infix expression: ";
    std::cin >> expr;
  }

  std::cout << "\npostfix: " << expr.to_postfix() << "\n\n";
  std::cout << "prefix: " << expr.to_prefix() << "\n\n";
  std::cout << "postfix evaluation: " << expr.evaluate_postfix() << "\n\n";
  std::cout << "prefix evaluation: " << expr.evaluate_prefix() << std::endl;

  std::cin.get();
  return 0;
}
