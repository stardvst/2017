#include <iostream>
#include "median.hpp"


int main() {

    Median<int> median("numbers.txt");

    std::cout << "median: " << median.get() << std::endl;


    std::cin.get();
    return 0;
}
