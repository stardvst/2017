#ifndef POSTFIX_HPP
#define POSTFIX_HPP

#include <string>


unsigned short priority(char);
bool is_operator(char);
bool is_operand(char);

std::string to_postfix(const std::string&);
void evaluate(const std::string&);

#endif // !POSTFIX_HPP
