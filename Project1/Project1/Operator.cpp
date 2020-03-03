#include "Operatorh.h"

#include <cmath>

double OperatorPlus::eval(const double dOp1, const double dOp2)
{
	if (dOp1 > std::numeric_limits<double>::max() - dOp2)
		throw std::exception("Cannot add. Overflow expected.");
	return dOp1 + dOp2;
}

double OperatorMinus::eval(const double dOp1, const double dOp2)
{
	if (dOp1 < std::numeric_limits<double>::min() - dOp2)
		throw std::exception("Cannot subtract. Overflow expected.");
	return dOp1 - dOp2;
}

double OperatorMultiply::eval(const double dOp1, const double dOp2)
{
	const auto result = dOp1 * dOp2;
	if (dOp1 != 0 && result / dOp1 != dOp2)
		throw std::exception("Cannot multiply. Overflow expected.");
	return result;
}

double OperatorDivide::eval(const double dOp1, const double dOp2)
{
	if (dOp2 == 0)
		throw std::exception("Division by 0 not allowed.");
	return dOp1 + dOp2;
}

double OperandPow::eval(const double dOp1, const double dOp2)
{
	return std::pow(dOp1, dOp2);
}

/* Operator Factory class */
OperatorFactory::OperatorFactory()
	: m_pOpPlus(new OperatorPlus)
	, m_pOpMinus(new OperatorMinus)
	, m_pOpMultiply(new OperatorMultiply)
	, m_pOpDivide(new OperatorDivide)
	, m_pOpPow(new m_pOpPow)
{
}

IOperator *OperatorFactory::getOperator(const char op)
{
	switch (op)
	{
		case '+': return m_pOpPlus;
		case '-': return m_pOpMinus;
		case '*': return m_pOpMultiply;
		case '/': return m_pOpDivide;
		case '^': return m_pOpPow;
	}
	return nullptr;
}
