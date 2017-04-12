#include <exception>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>
#include <cmath>
#include <map>
#include "prefix.hpp"


Prefix::Prefix(const std::string& in, const std::string& out)
  : infile(in), outfile(out) {}


void Prefix::evaluate() {

  if(infile.peek() == std::ifstream::traits_type::eof()) {
    outfile << "empty input";
    return;
  }

  std::string line;
  std::map<std::string, double> vars;

  while(std::getline(infile, line, '\n')) {

    if(!is_balanced(line)) {
      outfile << "expression is not balanced";
      return;
    }

    std::string prefix = infix_to_prefix(line);

    if(line.find('=') != std::string::npos) { // expression found
      std::string var = get_var_name(line);
      outfile << var << " = ";
      double expr_result = evaluate(prefix, vars);
      vars[var] = expr_result;
    } else {
      outfile << "\n---------------\n\n";
      outfile << "\n---------------\n" << evaluate(prefix, vars);
    }
  }

}


std::string Prefix::infix_to_prefix(const std::string& line) const {

  std::string reversed;

  if(line.find('=') != std::string::npos) {
    reversed = reverse(std::string(line, line.find('=') + 1)); // reverse string after =
  } else {
    reversed = reverse(line);
  }

  if(reversed[reversed.length() - 1] == '-') {
    reversed.append("0");
  }

  const size_t length = reversed.length();
  std::stack<char> operators;
  std::string prefix;

  for(size_t i = 0; i < length; ++i) {
    if(std::isspace(reversed[i])) {
      continue;
    } else if(std::isdigit(reversed[i])) {
      prefix += reversed[i];
    } else if(is_operator(reversed[i])) {
      prefix += ' ';
      while((!operators.empty() &&
             operators.top() != ')' &&
             priority(operators.top()) > priority(reversed[i])) ||
             (!operators.empty() && operators.top() == '^' && reversed[i] == '^')) {
        prefix += operators.top();
        prefix += ' ';
        operators.pop();
      }
      operators.push(reversed[i]);
    } else if(std::isalpha(reversed[i])) {
      while(i < length && std::isalpha(reversed[i])) {
        prefix += reversed[i++];
      }
      --i;
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

      operators.pop();
    } else if(reversed[i] == '.') {
      prefix += reversed[i];
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


std::string Prefix::reverse(const std::string& str) const {
  std::stringstream reversed;

  const int length = static_cast<int>(str.length());
  for(int i = length - 1; i >= 0; ) {
    if(std::isdigit(str[i])) {
      double number = get_number(str, i);
      if(i > 0 && str[i] == '.') { // double found
        double real_part = get_number(str, --i);
        reversed << real_part << '.' << number;
      } else {
        reversed << number;
      }
    } else if(std::isalpha(str[i])) {
      std::string var;
      while(std::isalpha(str[i])) {
        var += str[i--];
      }
      std::reverse(var.begin(), var.end());
      reversed << var;
    } else if(str[i] != ';') {
      reversed << str[i--];
    } else {
      --i;
    }
  }
  return reversed.str();
}


double Prefix::evaluate(const std::string& line, const std::map<std::string, double>& vars) {

  std::stack<std::string> tokens;
  std::stack<int> counts;

  const int length = static_cast<int>(line.length());
  for(int i = 0; i < length; ++i) {
    if(std::isspace(line[i])) {
      continue;
    }

    if(is_operator(line[i])) {
      tokens.push(std::string(1, line[i]));
      counts.push(2); // wait for 2 operands
    } else {
      if(std::isdigit(line[i])) {

        double token = 0;
        while(i < length && std::isdigit(line[i])) {
          token = 10 * token + (line[i] - '0');
          ++i;
        }
        if(i < length && line[i] == '.') {
          ++i;
          double precision = 10.0;
          while(i < length && std::isdigit(line[i])) {
            token = token + (line[i] - '0') / precision;
            precision *= 10;
            ++i;
          }
        }

        tokens.push(std::to_string(token));
      } else if(std::isalpha(line[i])) {
        std::string var;
        while(std::isalpha(line[i])) {
          var += line[i++];
        }
        --i;

        std::map<std::string, double>::const_iterator it = vars.find(var);
        if(it == vars.end()) {
          outfile << "identifier \"" << var << "\" is undefined";
          throw std::logic_error("unknown identifier\n");
        } else {
          tokens.push(std::to_string((*it).second));
        }
      }

      if(counts.empty()) {
        outfile << "wrong input";
        throw std::logic_error("wrong input\n");
      }
      update_counts(counts);

      while(counts.top() == 0) { // both operands found
        double result = calculate(tokens);
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

  return std::stof(tokens.top());
}


double Prefix::calculate(std::stack<std::string>& tokens) {
  double operand2 = std::stod(tokens.top());
  tokens.pop();

  double operand1 = std::stod(tokens.top());
  tokens.pop();

  char oper = tokens.top()[0];
  tokens.pop();

  outfile << operand1 << " " << oper << " " << operand2 << " = ";

  switch(oper) {
    case '+': return operand1 + operand2;
    case '-': return operand1 - operand2;
    case '*': return operand1 * operand2;
    case '/': return operand1 / operand2;
    case '^': return pow(operand1, operand2);
    default:
      return 0;
  }
}

void Prefix::update_counts(std::stack<int>& counts) const {
  if(!counts.empty()) {
    int last = counts.top();
    counts.pop();
    counts.push(--last);
  }
}

std::string Prefix::get_var_name(const std::string& line) const {
  std::string var;
  for(size_t i = 0; line[i] != '='; ++i) {
    if(!std::isspace(line[i])) {
      var += line[i];
    }
  }
  return var;
}

bool Prefix::is_operator(char c) const {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

unsigned short Prefix::priority(char c) const {
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

bool Prefix::is_balanced(const std::string& line) const {
  const size_t length = line.length();

  if(is_operator(line[length - 1]) || line[length - 1] == '.' ||
    (is_operator(line[0]) && line[0] != '-')) {
    return false;
  }


  std::stack<char> parentheses;

  for(size_t i = 0; i < length; ++i) {
    if(line[i] == '(') {
      parentheses.push(line[i]);
    } else if(line[i] == ')') {
      if(match(parentheses, line[i])) {
        parentheses.pop();
      } else {
        return false;
      }
    } else if(is_operator(line[i]) && i < length - 1 && is_operator(line[i + 1])) {
      return false;
    }
  }

  if(!parentheses.empty()) {
    return false;
  }

  return true;
}

bool Prefix::match(const std::stack<char>& parentheses, char closing) const {
  if(!parentheses.empty()) {
    switch(closing) {
      case ')':
        return parentheses.top() == '(';
    }
  }
  return false;
}

double Prefix::get_number(const std::string& line, int& i) const {
  double token = 0;
  int digits = 0;
  while(i >= 0 && std::isdigit(line[i])) {
    token += pow(10, digits) * (line[i] - '0');
    ++digits;
    --i;
  }
  return token;
}
