#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iosfwd>
#include <string>


class Expression {
  friend std::istream& operator>>(std::istream&, Expression&);
public:
  Expression(const std::string& = std::string());
  std::string to_postfix();
  std::string to_prefix();
  double evaluate_postfix() const;
  double evaluate_prefix() const;
  operator std::string() const;
private:
  std::string infix;
  std::string postfix;
  std::string prefix;
private:
  unsigned short priority(char) const;
  bool is_operator(char) const;
  bool is_operand(char) const;
  bool is_variable(char) const;
  std::string reverse(const std::string&);
};

#endif // !EXPRESSION_HPP
