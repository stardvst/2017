#include "Operand.h"

Operand::Operand(const int nValue)
	: m_sValue(std::to_string(nValue))
{
}

Operand::Operand(const double dValue)
	: m_sValue(std::to_string(dValue))
{
}

Operand::Operand(const std::string &sValue)
	: m_sValue(sValue)
{
}

int Operand::as_int() const
{
	return std::stoi(m_sValue);
}

double Operand::as_double() const
{
	return std::stod(m_sValue);
}

const std::string &Operand::as_string() const
{
	return m_sValue;
}
