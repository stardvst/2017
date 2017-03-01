#ifndef MAKE_STACK
#define MAKE_STACK

#include "LStack.hpp"


template<typename T>
void make_stack(Stack<T>* s1, Stack<T>* s2, Stack<T>* result) {
  bool t = true;
  
  while(!s1->empty() && !s2->empty()) {
    if(t) {
      result->push(s1->top());
      s1->pop();
      t = false;
    } else {
      result->push(s2->top());
      s2->pop();
      t = true;
    }
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
