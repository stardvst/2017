#include <iostream>
#include "LStack.hpp"
#include "LQueue.hpp"


int main() {

  char c;
  LQueue<char> queue;

  std::cin >> c;
  while(c != '!') {
    queue.enqueue(c);
    std::cin >> c;
  }

  LStack<char> stack;
  const size_t size = queue.size();

  for(int i = 0; i < size / 2; ++i) {
    stack.push(queue.front());
    queue.dequeue();
  }

  if(size & 1) {
    queue.dequeue();
  }

  bool flag = true;
  while(!stack.empty()) {
    if(stack.top() != queue.front()) {
      flag = false;
      break;
    }
    stack.pop();
    queue.dequeue();
  }

  std::cout << "is palindrome: " << std::boolalpha << flag << std::endl;

  std::cin.get();
  std::cin.get();
  return 0;
}
