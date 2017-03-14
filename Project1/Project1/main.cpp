#include <iostream>
#include <cassert>
#include <stack>


class Queue {
public:
  void enqueue(int);
  void dequeue();
  int front() const;
  size_t size() const;
  bool empty() const;
private:
  mutable std::stack<int> input;
  mutable std::stack<int> output;
};


void Queue::enqueue(int x) {
  input.push(x);
}

void Queue::dequeue() {
  if(output.empty()) {
    while(!input.empty()) {
      output.push(input.top());
      input.pop();
    }
  } else {
    output.pop();
  }
}

int Queue::front() const {
  if(output.empty()) {
    while(!input.empty()) {
      output.push(input.top());
      input.pop();
    }
    if(!output.empty()) {
      return output.top();
    }
  } else {
    return output.top();
  }

  return -1;
}

size_t Queue::size() const {
  return input.size() + output.size();
}

bool Queue::empty() const {
  return input.empty() && output.empty();
}


int main() {

  int size = 0;
  while(size <= 0) {
    std::cout << "enter queue size: ";
    std::cin >> size;
  }

  Queue queue;

  std::cout << std::boolalpha;
  std::cout << "\nsize: " << queue.size() << '\n'
    << "is empty: " << queue.empty() << "\n\n";

  std::cout << "enter queue elements:\n";
  int current;
  for(int i = 0; i < size; ++i) {
    std::cout << "queue[" << i << "] = ";
    std::cin >> current;
    queue.enqueue(current);
  }

  std::cout << "\nsize: " << queue.size() << '\n'
    << "is empty: " << queue.empty() << "\n\n";

  std::cout << "queue: ";
  while(!queue.empty()) {
    std::cout << queue.front() << ' ';
    queue.dequeue();
  }
  
  std::cout << std::endl;

  std::cin.get();
  std::cin.get();
  return 0;
}
