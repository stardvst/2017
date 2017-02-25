#include <iostream>
#include <string>
#include "AStack.hpp"
#include "LStack.hpp"
#include "balanced_parentheses.hpp"


int main() {

  int number = 0;
  while(number <= 0) {
    std::cout << "enter array-based stack size: ";
    std::cin >> number;
  }

  Stack<int>* stack = new AStack<int>(number);

  int current;
  for(int i = 0; i < number; ++i) {
    std::cout << "stack[" << i << "] = ";
    std::cin >> current;
    stack->push(current);
  }

  while(!stack->empty()) {
    std::cout << stack->top() << ' ';
    stack->pop();
  }

  delete stack;


  stack = new LStack<int>;

  for(number = 0; number <= 0; ) {
    std::cout << "\n\nenter linked stack size: ";
    std::cin >> number;
  }
  for(int i = 0; i < number; ++i) {
    std::cout << "stack[" << i << "] = ";
    std::cin >> current;
    stack->push(current);
  }

  while(!stack->empty()) {
    std::cout << stack->top() << ' ';
    stack->pop();
  }

  std::string str;
  std::cout << "\n\nenter parentheses: ";
  std::cin >> str;

  std::cout << "\nparentheses are " << (balanced(str) ? "balanced" : "not balanced");

  std::cin.get();
  std::cin.get();
}
