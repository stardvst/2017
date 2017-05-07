#include <exception>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <thread>
#include <vector>
#include <string>
#include <cctype>
#include <stack>
#include <mutex>
#include <cmath>
#include "Calc.hpp"


std::mutex Calc::m;


Calc::Calc(const std::string& of, const std::vector<std::string>& args) : outfile(of), argv(args) {}


void Calc::evaluate() {
    std::string var = get_varname(argv[1]);
    std::string function = get_function(argv[1]);

    if(var == "" || function == "") {
        std::cerr << "Variable and function can't be empty.\n";
        return;
    }
    if(function.find(var) == std::string::npos) {
        std::cerr << "The function must contain the variable " << var << '\n';
        return;
    }
    if(unknown_identifier_found(function, var)) {
        std::cerr << "Function should contain only " << var << ".\n";
        return;
    }


    std::pair<int, int> range = get_range(var, argv[2]);

    if(range.first == 0 && range.second == 0) {
        std::cerr << "Incorrect range format.\n";
        return;
    }
    if(range.first == -1 && range.second == -1) {
        std::cerr << "Range should be assigned to the variable " << var << ".\n";
        return;
    }


    double step = get_step(argv[3]);
    if(step == 0) {
        std::cerr << "wrong step, step = 0: infinite loop.\n";
        return;
    }


    function = to_postfix(function);

    outfile <<
        std::setw(11) << "x" <<
        std::setw(11) << "|" <<
        std::setw(13) << "y" <<
        "\n---------------------------------------------\n";

    function = minimize(function, var);



    if(range.second - range.first <= 100) {
        for(double value = range.first; value <= range.second; value += step) {
            evaluate_postfix(function, var, value);
        }
    } else {
        double start = range.first;
        double end = range.second;
        double length = end - start;

        std::thread t1(&Calc::evaluate_multithreaded, this, function, var, start, start + length / 4, step);
        std::thread t2(&Calc::evaluate_multithreaded, this, function, var, start + length / 4 + 1, start + length / 2, step);
        std::thread t3(&Calc::evaluate_multithreaded, this, function, var, start + length / 2 + 1, start + 3 * length / 4, step);
        std::thread t4(&Calc::evaluate_multithreaded, this, function, var, start + 3 * length / 4 + 1, end, step);

        if(t1.joinable()) {
            t1.join();
        }
        if(t2.joinable()) {
            t2.join();
        }
        if(t3.joinable()) {
            t3.join();
        }
        if(t4.joinable()) {
            t4.join();
        }
    }


}


std::string Calc::get_varname(const std::string& str) const {
    if(!is_function(str)) {
        return "";
    }

    std::string var;
    int i = 0;
    while(std::isalnum(str[i])) {
        ++i;
    }

    while(std::isalnum(str[++i])) {
        var += str[i];
    }

    return var;
}


std::string Calc::get_function(const std::string& str) const {
    int i = 0;
    const size_t length = str.length();
    while(i < length && str[i] != '=') {
        ++i;
    }
    ++i;

    std::string function;
    while(i < length) {
        function += str[i++];
    }
    return function;
}


std::pair<int, int> Calc::get_range(const std::string& var, const std::string& str) const {
    std::pair<int, int> range(0, 0);
    std::string range_var;

    int i = 0;
    const size_t length = str.length();
    while(str[i] != '=' && i < length) {
        range_var += str[i++];
    }

    if(var == range_var) {

        bool negative_start = false;
        if(str[i + 1] == '-') {
            negative_start = true;
            ++i;
        }

        int range_start = str[++i] - '0';
        while(str[++i] != '.' && i < length) {
            range_start = 10 * range_start + (str[i] - '0');
        }

        if(i == length - 1) {
            range_start = 0;
        }

        int range_end = 0;
        bool rend_exists = false;
        bool negative_end = false;

        while(i < length) {
            if(str[i] == '.') {
                ++i;
            } else if(str[i] >= '0' && str[i] <= '9') {
                rend_exists = true;
                range_end = 10 * range_end + (str[i++] - '0');
            } else if(str[i++] == '-') {
                negative_end = true;
            } else {
                return std::make_pair<int, int>(0, 0);
            }
        }

        if(rend_exists) {
            range.first = negative_start ? -range_start : range_start;
        }
        range.second = negative_end ? -range_end : range_end;
    } else {
        return std::make_pair<int, int>(-1, -1);
    }

    return range;
}



double Calc::get_step(const std::string& str) const {
    const size_t length = str.length();
    for(int i = 0; i < length; ++i) {
        if(!std::isdigit(str[i]) && str[i] != '.') {
            return 0;
        }
    }
    return std::stod(str);
}


std::string Calc::to_postfix(const std::string& infix) const {
    std::string postfix;
    std::stack<char> operators;

    const size_t length = infix.length();

    if(infix[0] == '-') {
        postfix += '0';
    }

    for(size_t i = 0; i < length; ++i) {
        if(std::isalnum(infix[i])) {
            postfix += infix[i];
        } else if(infix[i] == '(') {
            operators.push(infix[i]);
            if(i < length - 1 && infix[i + 1] == '-') {
                postfix += '0';
            }
        } else if(infix[i] == ')') {
            while(!operators.empty() && operators.top() != '(') {
                postfix += ' ';
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();

        } else if(is_operator(infix[i])) {
            postfix += ' ';
            while(!operators.empty() &&
                  operators.top() != '(' &&
                  priority(operators.top()) >= priority(infix[i])) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(infix[i]);
        } else if(infix[i] == '.') {
            postfix += infix[i];
        }
    }

    while(!operators.empty()) {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}


std::string Calc::minimize(const std::string& function, const std::string& var) const {
    std::stack<std::string> operands;
    const size_t length = function.length();

    for(size_t i = 0; i < length; ++i) {
        if(std::isspace(function[i])) {
            continue;
        }
        std::string var_in_function;
        if(std::isalpha(function[i])) { // var found
            while(std::isalpha(function[i])) {
                var_in_function += function[i++];
            }
            if(var_in_function == var) {
                operands.push(var);
            } else {
                std::cerr << var_in_function << " isn't a variable.\n";
                return "";
            }
        } else if(std::isdigit(function[i])) {
            double token = function[i] - '0';
            while(i < length && !std::isspace(function[++i])) {
                token = 10 * token + (function[i] - '0');
            }

            if(std::floor(token) == std::ceil(token)) {
                operands.push(std::to_string(static_cast<int>(token)));
            } else {
                operands.push(std::to_string(token));
            }

        } else if(is_operator(function[i])) {
            std::string op2 = operands.top();
            operands.pop();

            std::string op1 = operands.top();
            operands.pop();

            if(op1.find(var) == std::string::npos && op2.find(var) == std::string::npos) {
                double result = 0;
                switch(function[i]) {
                    case '+': result = std::stod(op1) + std::stod(op2); break;
                    case '-': result = std::stod(op1) - std::stod(op2); break;
                    case '*': result = std::stod(op1) + std::stod(op2); break;
                    case '/': result = std::stod(op1) + std::stod(op2); break;
                    case '^': result = std::pow(std::stod(op1), std::stod(op2)); break;
                }

                if(std::floor(result) == std::ceil(result)) {
                    operands.push(std::to_string(static_cast<int>(result)));
                } else {
                    operands.push(std::to_string(result));
                }
            } else {
                operands.push(op1 + function[i] + op2);
            }
        }
    }

    return to_postfix(operands.top());
}


void Calc::evaluate_postfix(const std::string& postfix, const std::string& var, double value) {
    std::stack<double> operands;
    const size_t length = postfix.length();

    for(size_t i = 0; i < length; ++i) {
        std::string var_in_function;
        if(std::isalpha(postfix[i])) { // var found
            while(std::isalpha(postfix[i])) {
                var_in_function += postfix[i++];
            }
            if(var_in_function == var) {
                operands.push(value);
            } else {
                std::cerr << var_in_function << " isn't a variable.\n";
                return;
            }
        } else if(std::isdigit(postfix[i])) {
            double token = postfix[i] - '0';
            while(i < length && !std::isspace(postfix[++i])) {
                token = 10 * token + (postfix[i] - '0');
            }

            operands.push(token);
        } else if(is_operator(postfix[i])) {
            double op2 = operands.top();
            operands.pop();

            double op1 = operands.top();
            operands.pop();

            switch(postfix[i]) {
                case '+': operands.push(op1 + op2); break;
                case '-': operands.push(op1 - op2); break;
                case '*': operands.push(op1 * op2); break;
                case '/': operands.push(op1 / op2); break;
                case '^': operands.push(pow(op1, op2)); break;
            }
        }
    }

    double result = operands.top();

    outfile << std::setw(11);
    if(std::floor(value) == std::ceil(value)) {
        outfile << static_cast<int>(value);
    } else {
        outfile << std::fixed << std::setprecision(2) << value;
    }
    outfile << std::setw(11) << "|" << std::setw(13);
    if(std::floor(result) == std::ceil(result)) {
        outfile << static_cast<int>(result);
    } else {
        outfile << std::fixed << std::setprecision(2) << result;
    }
    outfile << '\n';
}


void Calc::evaluate_multithreaded(const std::string& postfix, const std::string& var,
                                  double start, double end, double step) {
    m.lock();
    for(double value = start; value <= end; value += step) {
        evaluate_postfix(postfix, var, value);
    }
    m.unlock();
}


bool Calc::is_function(const std::string& str) const {
    if(!std::isalpha(str[0])) {
        return false;
    }

    int i = 0;
    const size_t length = str.length();
    while(std::isalnum(str[i]) && i < length) {
        ++i;
    }

    if(str[i] != '(') {
        return false;
    }

    bool var_exists = false;
    while(i < length) {
        ++i;
        if(std::isalnum(str[i])) {
            var_exists = true;
        } else if(str[i] == ')' && str[i + 1] == '=' && var_exists) {
            return true;
        }
    }

    return false;
}


bool Calc::is_operator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}


unsigned short Calc::priority(char c) const {
    switch(c) {
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

bool Calc::unknown_identifier_found(const std::string& function, const std::string& var) const {
    const size_t length = function.length();

    for(size_t i = 0; i < length; ++i) {
        if(std::isalpha(function[i])) {
            std::string var_in_function;
            while(std::isalpha(function[i])) {
                var_in_function += function[i++];
            }

            if(var_in_function != var) {
                return true;
            }
        }
    }

    return false;
}
