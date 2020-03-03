#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <cctype>
#include <stack>
#include <regex>
#include <mutex>
#include "Calc.h"

#include "Operand.h"
#include "Operator.h"

std::mutex Calc::m;

Calc::Calc(const std::string& of, const std::vector<std::string>& args)
	: outfile(of)
	, argv(args)
	, m_pOperatorFactory(new OperatorFactory)
{
}

void Calc::evaluate()
{
	std::regex regex1(".*\\(([a-zA-Z]+)\\)=(.*)");
	std::regex regex2("([+-]?[0-9]+(.[0-9]+)?)..([+-]?[0-9]+(.[0-9]+)?)");
	std::regex regex3("[+-]?[0-9]+(.[0-9]+)?");

	std::smatch var_and_function;
	std::smatch range;
	std::smatch step;

	std::regex_match(argv[1], var_and_function, regex1);
	std::regex_match(argv[2], range, regex2);
	std::regex_match(argv[3], step, regex3);

	if (var_and_function.size() == 3 && range.size() == 5 && step.size() == 2)
	{
		std::string var = var_and_function.str(1);
		std::string function = to_postfix(var_and_function.str(2));
		double range_start = std::stod(range.str(1));
		double range_end = std::stod(range.str(3));
		double the_step = std::stod(step.str(0));

		function = minimize(function, var);

		outfile << std::setw(11) << "x" << std::setw(11) << "|" << std::setw(13) << "y" <<
			"\n---------------------------------------------\n";

		if (range_end - range_start < 4096 / max_threads)
		{
			for (double value = range_start; value <= range_end; value += the_step)
			{
				evaluate_postfix(function, var, value);
			}
		}
		else
		{
			const double range_length = (range_end - range_start) / max_threads;

			std::vector<std::thread> threads;

			for (int i = 0; i < max_threads; ++i)
			{
				threads.emplace_back([&]
				{
					evaluate_multithreaded(function, var,
						range_start + i * range_length + (i == 0 ? 0 : 1), range_start + (i + 1) * range_length,
						the_step);
				});
				threads[i].detach();
			}

			threads.clear();
		}
	}
}

std::string Calc::to_postfix(const std::string& infix) const
{
	std::string postfix;
	std::stack<char> operators;

	const size_t length = infix.length();

	if (infix[0] == '-')
		postfix += '0';

	for (size_t i = 0; i < length; ++i)
	{
		if (std::isalnum(infix[i]))
			postfix += infix[i];
		else if (infix[i] == '(')
		{
			operators.push(infix[i]);
			if (i < length - 1 && infix[i + 1] == '-')
			{
				postfix += '0';
			}
		}
		else if (infix[i] == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				postfix += ' ';
				postfix += operators.top();
				operators.pop();
			}
			operators.pop();
		}
		else if (is_operator(infix[i]))
		{
			postfix += ' ';
			while (!operators.empty() && operators.top() != '(' && priority(operators.top()) >= priority(infix[i]))
			{
				postfix += operators.top();
				postfix += ' ';
				operators.pop();
			}
			operators.push(infix[i]);
		}
		else if (infix[i] == '.')
			postfix += infix[i];
	}

	while (!operators.empty())
	{
		postfix += ' ';
		postfix += operators.top();
		operators.pop();
	}

	return postfix;
}


std::string Calc::minimize(const std::string& function, const std::string& var) const
{
	std::stack<Operand> operands;
	const size_t length = function.length();

	for (size_t i = 0; i < length; ++i)
	{
		if (std::isspace(function[i]))
			continue;

		std::string var_in_function;
		if (std::isalpha(function[i]))
		{ // var found
			while (std::isalpha(function[i]))
				var_in_function += function[i++];

			if (var_in_function == var)
				operands.push(Operand(var));
			else
			{
				std::cerr << var_in_function << " isn't a variable.\n";
				return "";
			}
		}
		else if (std::isdigit(function[i]))
		{
			double token = function[i] - '0';
			while (i < length && !std::isspace(function[++i]))
				token = 10 * token + (function[i] - '0');

			if (std::floor(token) == std::ceil(token))
				operands.push(Operand(static_cast<int>(token)));
			else
				operands.push(Operand(token));

		}
		else if (is_operator(function[i]))
		{
			auto op2 = operands.top();
			operands.pop();

			auto op1 = operands.top();
			operands.pop();

			if (op1.as_string().find(var) == std::string::npos && op2.as_string().find(var) == std::string::npos)
			{
				// get the operands
				auto dOp1 = op1.as_double();
				auto dOp2 = op2.as_double();

				// calculate the result
				auto pOperator = m_pOperatorFactory->getOperator(function[i]);
				auto result = pOperator->eval(dOp1, dOp2);

				// is result an int or a double?
				if (std::floor(result) == std::ceil(result))
					operands.push(Operand(static_cast<int>(result)));
				else
					operands.push(Operand(result));
			}
			else
				operands.push(Operand(op1.as_string() + function[i] + op2.as_string()));
		}
	}

	return to_postfix(operands.top().as_string());
}

void Calc::evaluate_postfix(const std::string& postfix, const std::string& var, double value)
{
	std::stack<Operand> operands;
	const size_t length = postfix.length();

	for (size_t i = 0; i < length; ++i)
	{
		std::string var_in_function;
		if (std::isalpha(postfix[i]))
		{ // var found
			while (std::isalpha(postfix[i]))
				var_in_function += postfix[i++];

			if (var_in_function == var)
				operands.push(Operand(value));
			else
			{
				std::cerr << var_in_function << " isn't a variable.\n";
				return;
			}
		}
		else if (std::isdigit(postfix[i]))
		{
			double token = postfix[i] - '0';
			while (i < length && !std::isspace(postfix[++i]))
				token = 10 * token + (postfix[i] - '0');

			operands.push(Operand(token));
		}
		else if (is_operator(postfix[i]))
		{
			double dOp2 = operands.top().as_double();
			operands.pop();

			double dOp1 = operands.top().as_double();
			operands.pop();

			auto pOperator = m_pOperatorFactory->getOperator(postfix[i]);
			auto result = pOperator->eval(dOp1, dOp2);
			operands.push(Operand(result));
		}
	}

	double result = operands.top().as_double();

	// write formatted result in file
	outfile << std::setw(11);
	if (std::floor(value) == std::ceil(value))
		outfile << static_cast<int>(value);
	else
		outfile << std::fixed << std::setprecision(2) << value;
	
	outfile << std::setw(11) << "|" << std::setw(13);
	if (std::floor(result) == std::ceil(result))
		outfile << static_cast<int>(result);
	else
		outfile << std::fixed << std::setprecision(2) << result;
	
	outfile << '\n';
}

void Calc::evaluate_multithreaded(const std::string& postfix, const std::string& var,
	double start, double end, double step)
{
	std::lock_guard<std::mutex> lock(m);
	for (double value = start; value <= end; value += step)
		evaluate_postfix(postfix, var, value);
}

bool Calc::is_operator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

unsigned short Calc::priority(char c) const
{
	switch (c)
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		default:
			return 0;
	}
}