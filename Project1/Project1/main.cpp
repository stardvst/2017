#include <iostream>
#include <cassert>
#include <queue>


class Stack {
public:
  void push(int);
  void pop();
  int top() const;
  size_t size() const;
  bool empty() const;
private:
  mutable std::queue<int> queue1;
  mutable std::queue<int> queue2;
};


void Stack::push(int x) {
  queue1.push(x);
}

void Stack::pop() {
  if(!queue1.empty()) {
    while(queue1.size() != 1) {
      queue2.push(queue1.front());
      queue1.pop();
    }
    queue1.pop();
  } else {
    while(queue2.size() != 1) {
      queue1.push(queue2.front());
      queue2.pop();
    }
    queue2.pop();
  }
}

int Stack::top() const {
  int value = 0;

  if(!queue1.empty()) {
    while(!queue1.empty()) {
      value = queue1.front();
      queue2.push(value);
      queue1.pop();
    }
  } else {
    while(!queue2.empty()) {
      value = queue2.front();
      queue1.push(value);
      queue2.pop();
    }
  }

  return value;
}

size_t Stack::size() const {
  return queue1.size() + queue2.size();
}

bool Stack::empty() const {
  return queue1.empty() && queue2.empty();
}



int main() {

  int size = 0;
  while(size <= 0) {
    std::cout << "enter stack size: ";
    std::cin >> size;
  }

  Stack stack;

  std::cout << std::boolalpha;
  std::cout << "\nsize: " << stack.size() << '\n'
    << "is empty: " << stack.empty() << "\n\n";

  std::cout << "enter stack elements:\n";
  int current;
  for(int i = 0; i < size; ++i) {
    std::cout << "stack[" << i << "] = ";
    std::cin >> current;
    stack.push(current);
  }

  std::cout << "\nsize: " << stack.size() << '\n'
    << "is empty: " << stack.empty() << "\n\n";

  std::cout << "stack: ";
  while(!stack.empty()) {
    std::cout << stack.top() << ' ';
    stack.pop();
  }

  std::cout << std::endl;

  std::cin.get();
  std::cin.get();
  return 0;
}
