#include <iostream>
#include <cassert>
#include <memory>


template<typename T>
class Deque {
public:
  Deque() : front(new Node), rear(new Node) { 
    front->next = rear; 
    rear->prev = front; 
  }
  ~Deque();

  void push_front(const T&);
  void push_back(const T&);

  T pop_front();
  T pop_back();

  size_t size() { return _size; }
  bool empty() const { return _size == 0; }
private:
  struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(T d = T(), Node* p = nullptr, Node* n = nullptr) 
      : data(d), prev(p), next(n) {}
  };

private:
  Node* front;
  Node* rear;
  size_t _size;
};


template<typename T>
Deque<T>::~Deque() {
  while(front->next != rear) {
    Node* tmp = front->next;
    front->next = front->next->next;
    delete tmp;
  }
  delete front;
  delete rear;
}

template<typename T>
void Deque<T>::push_front(const T& x) {
  front->next->prev = new Node(x, front, front->next);
  front->next = front->next->prev;
  ++_size;
}

template<typename T>
void Deque<T>::push_back(const T& x) {
  rear->prev->next = new Node(x, rear->prev, rear);
  rear->prev = rear->prev->next;
  ++_size;
}

template<typename T>
T Deque<T>::pop_front() {
  assert(front->next != rear);
  T value = front->next->data;
  Node* nextnext = front->next->next;
  delete front->next;

  front->next = nextnext;
  nextnext->prev = front;
  --_size;
  return value;
}

template<typename T>
T Deque<T>::pop_back() {
  assert(rear->prev != front);
  T value = rear->prev->data;
  Node* prevprev = rear->prev->prev;
  delete rear->prev;

  rear->prev = prevprev;
  prevprev->next = rear;
  --_size;
  return value;
}


int main() {

  std::unique_ptr<Deque<int>> deque(new Deque<int>);

  std::cout << "is empty? " << std::boolalpha << deque->empty()
    << "\nsize: " << deque->size();
  
  int number = 0;
  while(number <= 0) {
    std::cout << "\n\nenter element size to insert: ";
    std::cin >> number;
  }
  int current;
  for(int i = 0; i < number; ++i) {
    std::cout << "deque[" << i << "] = ";
    std::cin >> current;
    i % 2 == 0 ? deque->push_front(current) : deque->push_back(current);
  }

  
  while(!deque->empty()) {
    const size_t size = deque->size();
    std::cout << (size % 2 == 0 ? deque->pop_back() : deque->pop_front()) << " ";
  }

  std::cin.get();
  std::cin.get();
}
