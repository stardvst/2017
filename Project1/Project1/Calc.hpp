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
    std::string to_postfix(const std::string&) const;
    std::string minimize(const std::string&, const std::string&) const;
    void evaluate_postfix(const std::string&, const std::string&, double);

    void evaluate_multithreaded(const std::string&, const std::string&, double, double, double);

    bool is_operator(char) const;
    unsigned short priority(char) const;
private:
    std::ofstream outfile;
    std::vector<std::string> argv;

    static int max_threads;
    static std::mutex m;
};

#endif // !CALC_HPP
