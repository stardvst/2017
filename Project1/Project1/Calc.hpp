#ifndef CALC_HPP
#define CALC_HPP

#include <fstream>
#include <utility>
#include <random>
#include <string>


class Calc {
public:
    Calc(const std::string&, const std::vector<std::string>&);
    void evaluate();
private:
    std::string to_postfix(const std::string&) const;
    std::string minimize(const std::string&, const std::string&) const;
    void evaluate_postfix(const std::string&, const std::string&, double);

    void evaluate_random(const std::string&, const std::string&, int,
                         const std::uniform_real_distribution<>&, std::mt19937_64);

    bool is_operator(char) const;
    unsigned short priority(char) const;
private:
    std::ofstream outfile;
    std::vector<std::string> argv;
};

#endif // !CALC_HPP
