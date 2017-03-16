#ifndef BALANCED_HPP
#define BALANCED_HPP

#include <string>
#include <stack>


bool balanced(const std::string&);
bool match(const std::stack<char>&, char);
bool is_operator(char c);

#endif // !BALANCED_HPP
