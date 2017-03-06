#ifndef MAKE_STACK_HPP
#define MAKE_STACK_HPP

#include "LStack.hpp"


template<typename T>
void make_stack(Stack<T>* s1, Stack<T>* s2, Stack<T>* result) {

  while(!s1->empty() && !s2->empty()) {
    result->push(s1->top());
    s1->pop();
    result->push(s2->top());
    s2->pop();
  }

  while(!s1->empty()) {
    result->push(s1->top());
    s1->pop();
  }
  while(!s2->empty()) {
    result->push(s2->top());
    s2->pop();
  }
}


#endif // !MAKE_STACK
