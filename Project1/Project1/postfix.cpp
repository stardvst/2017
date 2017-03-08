#include <cassert>
#include <string>
#include <cmath>
#include "Stack.hpp"
#include "LStack.hpp"
#include "postfix.hpp"
#include "balanced_parentheses.hpp"


unsigned short priority(char c) {
  switch(c) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '^':
      return 3;
    default:
      assert(false);
      return 0;
  }
}

bool is_operator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool is_operand(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool is_variable(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

std::string to_postfix(const std::string& infix) {
  if(!balanced(infix)) {
    std::cerr << "\nthe expression is unbalanced.\n";
    return "";
  }

  LStack<char> operators;
  std::string postfix;

  for(size_t i = 0; i < infix.length(); ++i) {
    if(isspace(infix[i])) {
      continue;
    } else if(is_operand(infix[i])) {
      postfix += infix[i];
    } else if(infix[i] == '(') {
      operators.push(infix[i]);
    } else if(infix[i] == ')') {
      while(!operators.empty() && operators.top() != '(') {
        postfix += operators.top();
        operators.pop();
      }

      assert(!operators.empty());
      assert(operators.top() == '(');

      operators.pop();

    } else if(is_operator(infix[i])) {
      while(!operators.empty() &&
            operators.top() != '(' &&
            priority(operators.top()) >= priority(infix[i])) {
        postfix += operators.top();
        operators.pop();
      }

      operators.push(infix[i]);
    }
  }

  while(!operators.empty()) {
    postfix += operators.top();
    operators.pop();
  }

  return postfix;
}


void evaluate(const std::string& postfix) {
  LStack<double> operands;

  for(size_t i = 0; i < postfix.length(); ++i) {
    if(is_variable(postfix[i])) {
      double var;
      std::cout << postfix[i] << " = ";
      std::cin >> var;
      operands.push(var);
    } else if(is_operand(postfix[i])) {
      operands.push(postfix[i] - '0');
    } else if(is_operator(postfix[i])) {
      assert(!operands.empty());
      double op2 = operands.top();
      operands.pop();

      assert(!operands.empty());
      double op1 = operands.top();
      operands.pop();

      switch(postfix[i]) {
        case '+': operands.push(op1 + op2); break;
        case '-': operands.push(op1 - op2); break;
        case '*': operands.push(op1 * op2); break;
        case '/': operands.push(op1 / op2); break;
        case '^': operands.push(pow(op1, op2)); break;
        default: assert(false);
      }
    }
  }

  if(operands.empty()) {
    std::cerr << "wrong input, result: undefined\n";
    return;
  }
  
  std::cout << "\nresult: " << operands.top() << std::endl;
  operands.pop();
}