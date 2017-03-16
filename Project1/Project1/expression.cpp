#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include <cctype>
#include <stack>
#include <cmath>
#include "expression.hpp"
#include "balanced.hpp"


Expression::Expression(const std::string& expr) : infix(expr) {}

std::string Expression::to_postfix() {

  std::stack<char> operators;
  const size_t length = infix.length();

  if(infix[0] == '-') {
    postfix += '0';
  }

  for(size_t i = 0; i < length; ++i) {
    if(std::isspace(infix[i])) {
      continue;
    } else if(is_operand(infix[i])) {
      postfix += infix[i];
    } else if(infix[i] == '(') {
      operators.push(infix[i]);
      if(i < length - 1 && infix[i + 1] == '-') {
        postfix += '0';
      }
    } else if(infix[i] == ')') {
      while(!operators.empty() && operators.top() != '(') {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
      }

      assert(!operators.empty());
      assert(operators.top() == '(');
      operators.pop();

    } else if(is_operator(infix[i])) {
      postfix += ' ';
      while(!operators.empty() &&
            operators.top() != '(' &&
            priority(operators.top()) >= priority(infix[i])) {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
      }
      operators.push(infix[i]);
    }
  }

  while(!operators.empty()) {
    postfix += ' ';
    postfix += operators.top();
    operators.pop();
  }

  return postfix;
}

std::string Expression::to_prefix() {

  std::stack<char> operators;
  std::string reversed = reverse(infix);

  if(reversed[reversed.length() - 1] == '-') {
    reversed.append("0");
  }

  const size_t length = reversed.length();

  for(size_t i = 0; i < length; ++i) {
    if(std::isspace(reversed[i])) {
      continue;
    } else if(is_operand(reversed[i])) {
      prefix += reversed[i];
    } else if(reversed[i] == ')') {
      operators.push(reversed[i]);
    } else if(reversed[i] == '(') {
      if(reversed[i - 1] == '-') {
        prefix += '0';
      }
      while(!operators.empty() && operators.top() != ')') {
        prefix += ' ';
        prefix += operators.top();
        operators.pop();
      }

      assert(!operators.empty());
      assert(operators.top() == ')');
      operators.pop();
    } else if(is_operator(reversed[i])) {
      prefix += ' ';
      while(!operators.empty() &&
            operators.top() != ')' &&
            priority(operators.top() >= priority(reversed[i]))) {
        prefix += operators.top();
        prefix += ' ';
        operators.pop();
      }
      operators.push(reversed[i]);
    }
  }

  while(!operators.empty()) {
    prefix += ' ';
    prefix += operators.top();
    operators.pop();
  }

  prefix = reverse(prefix);
  return prefix;
}

double Expression::evaluate_postfix() const {
  std::stack<double> operands;
  const size_t length = postfix.length();

  for(size_t i = 0; i < length; ++i) {
    if(is_variable(postfix[i])) {
      double var;
      std::cout << postfix[i] << " = ";
      std::cin >> var;
      operands.push(var);
    } else if(is_operand(postfix[i])) {
      double token = postfix[i] - '0';
      while(i < length && !std::isspace(postfix[++i])) {
        token = 10 * token + (postfix[i] - '0');
      }

      operands.push(token);
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
      }
    }
  }

  return operands.top();
}

double Expression::evaluate_prefix() const {
  std::stack<double> operands;
  const int length = static_cast<int>(prefix.length());

  for(int i = length - 1; i >= 0; --i) {
    if(is_variable(prefix[i])) {
      double var;
      std::cout << prefix[i] << " = ";
      std::cin >> var;
      operands.push(var);
    } else if(is_operand(prefix[i])) {
      double token = prefix[i] - '0';
      int digits = 1;
      while(i > 0 && !std::isspace(prefix[--i])) {
        token = token + pow(10, digits) * (prefix[i] - '0');
        ++digits;
      }

      operands.push(token);
    } else if(is_operator(prefix[i])) {
      assert(!operands.empty());
      double op1 = operands.top();
      operands.pop();

      assert(!operands.empty());
      double op2 = operands.top();
      operands.pop();

      switch(prefix[i]) {
        case '+': operands.push(op1 + op2); break;
        case '-': operands.push(op1 - op2); break;
        case '*': operands.push(op1 * op2); break;
        case '/': operands.push(op1 / op2); break;
        case '^': operands.push(pow(op1, op2)); break;
      }
    }
  }

  return operands.top();
}

Expression::operator std::string() const {
  return infix;
}


unsigned short Expression::priority(char c) const {
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
      return 0;
  }
}


bool Expression::is_operator(char c) const {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Expression::is_operand(char c) const {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool Expression::is_variable(char c) const {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

std::string Expression::reverse(const std::string& str) {
  std::stringstream reversed;

  const int length = static_cast<int>(str.length());
  for(int i = length - 1; i >= 0; ) {
    if(is_operand(str[i])) {
      double token = str[i--] - '0';
      int digits = 1;
      while(i >= 0 && is_operand(str[i])) {
        token = token + pow(10, digits) * (str[i] - '0');
        ++digits;
        --i;
      }
      reversed << token;
    } else {
      reversed << str[i--];
    }
  }
  return reversed.str();
}


std::istream& operator>>(std::istream& is, Expression& expr) {
  std::getline(is, expr.infix);
  return is;
}