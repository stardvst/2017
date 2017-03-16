#include <iostream>
#include <string>
#include <stack>
#include "balanced.hpp"


bool balanced(const std::string& input) {
  const size_t length = input.length();

  if(is_operator(input[length - 1]) || 
    (is_operator(input[0]) && input[0] != '-')) {
    return false;
  }


  std::stack<char> parentheses;

  for(size_t i = 0; i < length; ++i) {
    if(input[i] == '(') {
      parentheses.push(input[i]);
    } else if(input[i] == ')') {
      if(match(parentheses, input[i])) {
        parentheses.pop();
      } else {
        return false;
      }
    } else if(is_operator(input[i]) && i < length - 1 && is_operator(input[i + 1])) {
      return false;
    }
  }

  if(!parentheses.empty()) {
    return false;
  }

  return true;
}

bool match(const std::stack<char>& parentheses, char closing) {
  if(!parentheses.empty()) {
    switch(closing) {
      case ')':
        return parentheses.top() == '(';
    }
  }
  return false;
}

bool is_operator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
