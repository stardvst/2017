#ifndef CALC_HPP
#define CALC_HPP

#include <fstream>
#include <utility>
#include <mutex>

class OperatorFactory;

class Calc
{
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

	static inline int max_threads = std::thread::hardware_concurrency();
	static std::mutex m;

	OperatorFactory *m_pOperatorFactory { nullptr };
};

#endif // !CALC_HPP
