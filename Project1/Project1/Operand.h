#ifndef OPERAND_H
#define OPERAND_H

#include <string>

class Operand
{
public:
	explicit Operand(const int nValue);
	explicit Operand(const double dValue);
	explicit Operand(const std::string &sValue);

	int as_int() const;
	double as_double() const;
	const std::string &as_string() const;

private:
	std::string m_sValue;
};

#endif
