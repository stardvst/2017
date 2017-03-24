#ifndef PREFIX_HPP
#define PREFIX_HPP

#include <fstream>
#include <string>
#include <stack>


class Prefix {
public:
  Prefix(const std::string&, const std::string&);
  void evaluate();
private:
  bool is_operator(const std::string&) const;
  bool is_operand(const std::string&) const;
  bool is_variable(const std::string&) const;
  double evaluate(std::stack<std::string>&);
  void update_counts(std::stack<int>&);
private:
  std::ifstream infile;
  std::ofstream outfile;
};

#endif // !PREFIX_HPP
