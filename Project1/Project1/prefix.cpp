#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cctype>
#include <stack>
#include <cmath>
#include "prefix.hpp"


Prefix::Prefix(const std::string& in, const std::string& out) 
  : infile(in), outfile(out) {}

void Prefix::evaluate() {

  if(infile.peek() == std::ifstream::traits_type::eof()) {
    outfile << "empty input";
    return;
  }

  std::stack<std::string> tokens;
  std::stack<int> counts;

  std::string token;
  while(infile >> token) {
    if(is_operator(token)) {
      tokens.push(token);
      counts.push(2); // wait for 2 operands
    } else {
      if(is_variable(token)) {
        int var;
        std::cout << token << " = ";
        std::cin >> var;
        tokens.push(std::to_string(var));
      } else if(is_operand(token)) {
        tokens.push(token);
      }

      if(counts.empty()) {
        outfile << "wrong input";
        return;
      }
      update_counts(counts);

      while(counts.top() == 0) { // both operands found
        double result = evaluate(tokens);
        tokens.push(std::to_string(result));
        outfile << result << '\n';
        counts.pop();
        update_counts(counts);
        if(counts.empty()) {
          break;
        }
      }

    }
  }

  assert(!tokens.empty());
  outfile << "\n---------------\n" << tokens.top();
}

bool Prefix::is_operator(const std::string& s) const {
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

bool Prefix::is_operand(const std::string& s) const {
  return s.find_first_not_of("0123456789") == std::string::npos;
}

bool Prefix::is_variable(const std::string& s) const {
  return (s >= "a" && s <= "z") || (s >= "A" && s <= "Z");
}

double Prefix::evaluate(std::stack<std::string>& tokens) {
  assert(!tokens.empty());
  int operand2 = std::stoi(tokens.top());
  tokens.pop();

  assert(!tokens.empty());
  int operand1 = std::stoi(tokens.top());
  tokens.pop();

  assert(!tokens.empty());
  char oper = tokens.top()[0];
  tokens.pop();

  //outfile << operand1 << " " << oper << " " << operand2 << " = ";
 
  switch(oper) {
    case '+': return operand1 + operand2;
    case '-': return operand1 - operand2;
    case '*': return operand1 * operand2;
    case '/': return operand1 / operand2;
    case '^': return pow(operand1, operand2);
    default:
      assert(false);
      return 0;
  }
}

void Prefix::update_counts(std::stack<int>& counts) {
  if(counts.empty()) {
    return;
  }
  int last = counts.top();
  counts.pop();
  counts.push(--last);
}