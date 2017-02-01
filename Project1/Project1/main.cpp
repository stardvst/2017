#include <iostream>
#include <string>
#include <stack>


int evaluate(const std::string& expression) {

  std::stack<int> operands;
  int result = 0;
  
  for(size_t i = 0; i < expression.length(); ++i) {
    if(expression[i] == ' ') {
      continue;
    } else if(isdigit(expression[i])) {
      operands.push(expression[i] - '0'); // convert ascii to int
    } else {
      int op1 = operands.top();
      operands.pop();
      int op2 = operands.top();
      operands.pop();

      switch(expression[i]) {
        case '+': operands.push(op2 + op1); break;
        case '-': operands.push(op2 - op1); break;
        case '*': operands.push(op2 * op1); break;
        case '/': operands.push(op2 / op1); break;
      }
    }
  }

  return operands.top();
}


int main() {

  std::cout << evaluate("231*+9-");

  std::cin.get();
  return 0;
}