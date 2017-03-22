#include <iostream>
#include "LStack.hpp"
#include "LQueue.hpp"


int main() {

  int number = 0;
  while(number <= 0) {
    std::cout << "enter queue size: ";
    std::cin >> number;
  }

  LQueue<int> queue;

  int current;
  for(int i = 0; i < number; ++i) {
    std::cout << "queue[" << i << "] = ";
    std::cin >> current;
    queue.enqueue(current);
  }


  LStack<int> stack;

  while(!queue.empty()) {
    stack.push(queue.front());
    queue.dequeue();
  }

  while(!stack.empty()) {
    queue.enqueue(stack.top());
    stack.pop();
  }

  std::cout << "\nreverse queue: ";
  while(!queue.empty()) {
    std::cout << queue.front() << ' ';
    queue.dequeue();
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
