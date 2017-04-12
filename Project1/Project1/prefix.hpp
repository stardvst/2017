#ifndef PREFIX_HPP
#define PREFIX_HPP

#include <fstream>
#include <string>
#include <stack>
#include <map>


class Prefix {
public:
  Prefix(const std::string&, const std::string&);
  void evaluate();
private:
  double evaluate(const std::string&, const std::map<std::string, double>&);

  std::string get_var_name(const std::string&) const;
  std::string infix_to_prefix(const std::string&) const;
  std::string reverse(const std::string&) const;

  double calculate(std::stack<std::string>&);
  void update_counts(std::stack<int>&) const;

  bool is_operator(char) const;
  unsigned short priority(char) const;

  bool is_balanced(const std::string&) const;
  bool match(const std::stack<char>&, char) const;

  double get_number(const std::string&, int&) const;
private:
  std::ifstream infile;
  std::ofstream outfile;
};

#endif // !PREFIX_HPP
