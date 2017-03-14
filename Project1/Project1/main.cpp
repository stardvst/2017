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
  std::queue<int> queue;
};


void Stack::push(int x) { // O(n)
  queue.push(x);
  for(size_t i = 0; i < queue.size() - 1; ++i) {
    queue.push(queue.front());
    queue.pop();
  }
}

void Stack::pop() { // O(1)
  assert(!queue.empty());
  queue.pop();
}

int Stack::top() const { // O(1)
  assert(!queue.empty());
  return queue.front();
}

size_t Stack::size() const { // O(1)
  return queue.size();
}

bool Stack::empty() const { // O(1)
  return queue.empty();
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
