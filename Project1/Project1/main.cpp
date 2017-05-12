#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "Calc.hpp"


int main(int argc, char* argv[]) {

    if(argc == 4) {
        std::vector<std::string> args(argv, argv + argc);

        Calc c("calc.txt", args);
        c.evaluate();
        std::cout << "see \"calc.txt\" for the result.";
    } else {
        std::cerr << "Usage: <program> <function> <range_start..range_end> <step>\n";
    }


    return 0;
}
