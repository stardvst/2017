#include <iostream>
#include <string>
#include <stack>

bool check_match(std::stack<char>& symbols, char symbol) {
  if(symbols.size() && 
     (symbol == ')' && symbols.top() == '(') ||
     (symbol == ']' && symbols.top() == '[') ||
     (symbol == '}' && symbols.top() == '{')) {
    symbols.pop();
    return true;
  }
  return false;
}

bool balancing_symbols_pascal(const std::string& input) {

  std::stack<char> symbols;
  bool balanced = true;

  for(size_t i = 0; i < input.length(); ++i) {
    switch(input[i]) {
    case '(': 
    case '[': 
    case '{': 
      symbols.push(input[i]); break;
    case 'b':
      if(i != input.length() - 4 &&
         input[i + 2] == 'g' &&
         input[i + 3] == 'i' &&
         input[i + 4] == 'n') {
        symbols.push('b');
        i += 3; // advaance i to point to the symbol after "begin"
      }
      break;
    case ')':
    case ']':
    case '}':
      balanced = check_match(symbols, input[i]);
      break;
    case 'e':
      if(i != input.length() - 2 &&
         input[i + 1] == 'n'&&
         input[i + 2] == 'd') {
        symbols.size() && symbols.top() == 'b' ? symbols.pop() : balanced = false;
        ++i; // advaance i to point to the symbol after "end"
      }
      break;
    default:
      break;
    }
  }

  if(!symbols.empty()) {
    balanced = false;
  }

  return balanced;
}

bool balancing_symbols_cpp(const std::string& input) {

  std::stack<char> symbols;
  bool balanced = true;

  for(size_t i = 0; i < input.length(); ++i) {
    switch(input[i]) {
    case '(':
    case '[':
    case '{':
      symbols.push(input[i]); break;
    case '/':
      if(i != input.length() - 1 &&
         input[i + 1] == '*') {
        symbols.push('/');
        ++i; // advaance i to point to the symbol after "/*"
      }
      break;
    case ')':
    case ']':
    case '}':
      balanced = check_match(symbols, input[i]);
      break;
    case '*':
      if(i != input.length() - 1 &&
         input[i + 1] == '/') {
        symbols.size() && symbols.top() == '/' ? symbols.pop() : balanced = false;
        ++i; // advaance i to point to the symbol after "end"
      }
      break;
    default:
      break;
    }
  }

  if(!symbols.empty()) {
    balanced = false;
  }

  return balanced;
}

int main() {

  std::string input;

  /* check for pascal */
  std::cout << "enter a code snippet in pascal:\n\n";
  
  std::string line = " ";
  while(line.length() != 0) {
    std::getline(std::cin, line);
    input += line;
  }

  std::cout << "the code in pascal is balanced: "
    << std::boolalpha << balancing_symbols_pascal(input) << "\n\n\n\n";

  /* check for c++ */
  std::cout << "enter a code snippet in c++:\n\n";

  line = " ";
  while(line.length() != 0) {
    std::getline(std::cin, line);
    input += line;
  }

  std::cout << "the code in c++ is balanced: "
    << std::boolalpha << balancing_symbols_cpp(input);

  std::cin.get();
  return 0;
}