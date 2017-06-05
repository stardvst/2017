#include <iostream>
#include <iomanip>
#include <stack>
#include <cmath>


int main() {

    std::stack<double> numbers;
    double number;
    while(std::cin >> number) {
        numbers.push(number);
    }

    while(!numbers.empty()) {
        std::cout << std::fixed << std::setprecision(4) << std::sqrt(numbers.top()) << '\n';
        numbers.pop();
    }

    std::cin.get();
    return 0;
}