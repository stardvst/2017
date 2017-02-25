#ifndef BALANCED_PARENTHESES
#define BALANCED_PARENTHESES

#include <iostream>
#include <string>
#include "LStack.hpp"


bool match(Stack<char>* stack, char closing) {
  if(!stack->empty()) {
    switch(closing) {
      case ')':
        return stack->top() == '(';
      case ']':
        return stack->top() == '[';
      case '}':
        return stack->top() == '{';
    }
  }
  return false;
}


bool balanced(std::string parentheses) {

  Stack<char>* stack = new LStack<char>;

  for(size_t i = 0; i < parentheses.length(); ++i) {
    switch(parentheses[i]) {
      case '(':
      case '[':
      case '{':
        stack->push(parentheses[i]);
        break;

      case ')':
      case ']':
      case '}':
        if(match(stack, parentheses[i])) {
          stack->pop();
        } else {
          return false;
        }
      default:
        break;
    }
  }

  if(!stack->empty()) {
    return false;
  }

  return true;
}

#endif // !BALANCED_PARENTHESES
