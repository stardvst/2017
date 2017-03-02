#include <iostream>
#include "LStack.hpp"
#include "make_stack.hpp"


int main() {

  LStack<int>* stack1 = new LStack<int>;
  LStack<int>* stack2 = new LStack<int>;

  int number = 0;
  while(number <= 0) {
    std::cout << "enter stack1 size: ";
    std::cin >> number;
  }
  int current;
  for(int i = 0; i < number; ++i) {
    std::cout << "stack1[" << i << "] = ";
    std::cin >> current;
    stack1->push(current);
  }

  for(number = 0; number <= 0; ) {
    std::cout << "\nenter stack2 size: ";
    std::cin >> number;
  }
  for(int i = 0; i < number; ++i) {
    std::cout << "stack2[" << i << "] = ";
    std::cin >> current;
    stack2->push(current);
  }

  LStack<int>* result = new LStack<int>;
  make_stack(stack1, stack2, result);

  std::cout << '\n';
  while(!result->empty()) {
    std::cout << result->top() << ' ';
    result->pop();
  }


  std::cin.get();
  std::cin.get();
  return 0;
}
