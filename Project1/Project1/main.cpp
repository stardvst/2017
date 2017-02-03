#include <iostream>
#include <string>
#include <cctype>
#include <stack>

double evaluate(const std::string& expression) {

  std::stack<double> operands;
  int result = 0;
  
  for(size_t i = 0; i < expression.length(); ++i) {
    if(isspace(expression[i])) {
      continue;
    } else if(isdigit(expression[i])) {
      operands.push(expression[i] - '0'); // convert ascii to int
    } else {
      double op1 = operands.top();
      operands.pop();
      double op2 = operands.top();
      operands.pop();

      switch(expression[i]) {
        case '+': operands.push(op2 + op1); break;
        case '-': operands.push(op2 - op1); break;
        case '*': operands.push(op2 * op1); break;
        case '/': operands.push(op2 / op1); break;
        case '^': operands.push(pow(op2, op1)); break;
      }
    }
  }

  return operands.top();
}


std::string to_postfix(const std::string& infix) {

  std::stack<char> operators;
  std::string result;

  for(size_t i = 0; i < infix.length(); ++i) {
    if(isspace(infix[i])) {
      continue;
    } else if(isdigit(infix[i])) {
      result += infix[i];
    } else {
      switch(infix[i]) {
        case '+':
        case '-':
          if(!operators.empty() && (operators.top() == '+' || operators.top() == '-' ||
                                  operators.top() == '*' || operators.top() == '/')) {
            result += operators.top();
            operators.pop();
            if(!operators.empty() && (operators.top() == '+' || operators.top() == '-')) {
              result += operators.top();
               operators.pop();
            }
          }
          operators.push(infix[i]);
          break;
        case '*':
        case '/':
          if(!operators.empty() && (operators.top() == '*' || operators.top() == '/')) {
            result += operators.top();
            operators.pop();
          }
          operators.push(infix[i]);
          break;
        case '^':
          if(!operators.empty() && (operators.top() == '^')) {
            result += '^';
          } else {
            operators.push('^');
          }
          break;
        case '(': 
          operators.push('(');
          break;
        case ')':
          while(operators.top() != '(') {
            result += operators.top();
            operators.pop();
          }
          operators.pop();
          break;
      }
    }
  }
  
  while(!operators.empty()) {
    result += operators.top();
    operators.pop();
  }
  return result;
}


struct Term {
  std::string expr;
  char oper;
  Term(std::string e, char o) : expr(e), oper(o) {}
};

std::string to_infix(const std::string& postfix) {

  std::stack<Term> operands;

  for(size_t i = 0; i < postfix.length(); ++i) {
    char left_prev_operator;
    char right_prev_operator;

    if(isspace(postfix[i])) {
      continue;
    } else if(isdigit(postfix[i])) {
      operands.push(Term(std::to_string(postfix[i] - '0'), '\0'));
    } else {
      Term op1 = operands.top();
      operands.pop();
      Term op2 = operands.top();
      operands.pop();
      
      std::string tmp;
      std::string right_expr = op1.expr;
      std::string left_expr = op2.expr;

      switch(postfix[i]) {
        case '*':
        case '/':
          if(op1.oper == '+' || op1.oper == '-') {
            right_expr = "(" + op1.expr + ")";
          }
          if(op2.oper == '+' || op2.oper == '-') {
            left_expr = "(" + op2.expr + ")";
          }
          tmp = left_expr + postfix[i] + right_expr;
          break;
        case '^':
          if(op1.oper == '*' || op1.oper == '/' || op1.oper == '+' || op1.oper == '-') {
            right_expr = "(" + op1.expr + ")";
          }
          if(op2.oper == '*' || op2.oper == '/' || op2.oper == '+' || op2.oper == '-') {
            left_expr = "(" + op2.expr + ")";
          }
          tmp = left_expr + postfix[i] + right_expr;
          break;
        default: // +, -
          tmp = op2.expr + postfix[i] + op1.expr;
          break;
      }

      operands.push(Term(tmp, postfix[i]));
    }
  }

  return operands.top().expr;
}


int main() {

  std::cout << evaluate(to_postfix("5+4*7+(5*3+4)*3")) << '\n'
    << evaluate(to_postfix("5*3^(4-2)")) << '\n'
    << to_infix(to_postfix("5+4*7+(5*3+4)*(4+5)")) << '\n'
    << to_infix(to_postfix("5*3^(4-2)")) << '\n'
    << to_infix(to_postfix("5-4-2"));

  std::cin.get();
  return 0;
}