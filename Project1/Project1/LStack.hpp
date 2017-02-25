#ifndef LSTACK_HPP
#define LSTACK_HPP

#include "Stack.hpp"


template<typename T>
class LStack : public Stack<T> {
public:
  LStack() : _top(0), _size(0) {}
  ~LStack();

  void push(const T&);
  void pop();

  T& top();

  bool empty() const { return _top == 0; }
  size_t size() const { return _size; }
private:
  struct Item {
    T data;
    Item* next;
    Item(T d, Item* n) : data(d), next(n) {}
  };

private:
  Item* _top;
  size_t _size;
};


template<typename T>
LStack<T>::~LStack() {
  while(_top) {
    Item* tmp = _top;
    _top = _top->next;
    delete tmp;
  }
}

template<typename T>
void LStack<T>::push(const T& x) {
  _top = new Item(x, _top);
  ++_size;
}

template<typename T>
void LStack<T>::pop() {
  assert(_top != 0);
  Item* tmp = _top;
  _top = _top->next;
  delete tmp;
  --_size;
}

template<typename T>
T& LStack<T>::top() {
  assert(_top != 0);
  return _top->data;
}


#endif // !LSTACK_HPP
