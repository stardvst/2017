#ifndef ASTACK_HPP
#define ASTACK_HPP

#include <cassert>
#include "Stack.hpp"


template<typename T>
class AStack : public Stack<T> {
public:
  AStack(size_t n) : stack(new T[n]), _top(0), _size(n) {}
  ~AStack() { delete[] stack; }

  void push(const T&);
  void pop();

  T& top();

  bool empty() const { return _top == 0; }
  size_t size() const { return _top; }
private:
  T* stack;
  size_t _top;
  size_t _size;
};


template<typename T>
void AStack<T>::push(const T& x) {
  assert(_top != _size);
  stack[_top++] = x;
}

template<typename T>
void AStack<T>::pop() {
  assert(!empty());
  --_top;
}

template<typename T>
T& AStack<T>::top() {
  assert(!empty());
  return stack[_top - 1];
}

#endif // !ASTACK_HPP
