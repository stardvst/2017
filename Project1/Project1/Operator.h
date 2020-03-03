#ifndef OPERATOR_H
#define OPERATOR_H

#include <limits>
#include <exception>

class IOperator
{
public:
	virtual double eval(const double dOp1, const double dOp2) = 0;
};

class OperatorPlus : public IOperator
{
public:
	double eval(const double dOp1, const double dOp2) override;
};

class OperatorMinus : public IOperator
{
public:
	double eval(const double dOp1, const double dOp2) override;
};

class OperatorMultiply : public IOperator
{
public:
	double eval(const double dOp1, const double dOp2) override;
};

class OperatorDivide : public IOperator
{
public:
	double eval(const double dOp1, const double dOp2) override;
};

class OperandPow : public IOperator
{
public:
	double eval(const double dOp1, const double dOp2) override;
};

/* A factory for operators */
class OperatorFactory
{
public:
	OperatorFactory();
	IOperator *getOperator(const char op);

private:
	OperatorPlus *m_pOpPlus { nullptr };
	OperatorMinus *m_pOpMinus { nullptr };
	OperatorMultiply *m_pOpMultiply { nullptr };
	OperatorDivide *m_pOpDivide { nullptr };
	OperandPow *m_pOpPow { nullptr };
};

#endif