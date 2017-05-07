#ifndef CALC_HPP
#define CALC_HPP

#include <fstream>
#include <utility>
#include <string>
#include <mutex>


class Calc {
public:
  Calc(const std::string&, const std::vector<std::string>&);
  void evaluate();
private:
  std::string get_varname(const std::string&) const;
  std::string get_function(const std::string&) const;
  std::pair<int, int> get_range(const std::string&, const std::string&) const;
  double get_step(const std::string&) const;

  std::string to_postfix(const std::string&) const;
  std::string minimize(const std::string&, const std::string&) const;
  void evaluate_postfix(const std::string&, const std::string&, double);
  
  void evaluate_multithreaded(const std::string&, const std::string&, double, double, double);

  bool is_function(const std::string&) const;
  bool is_operator(char) const;
  unsigned short priority(char) const;

  bool unknown_identifier_found(const std::string&, const std::string&) const;
private:
  std::ofstream outfile;
  std::vector<std::string> argv;

  static std::mutex m;
};

#endif // !CALC_HPP
