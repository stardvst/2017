#include <functional>
#include <iostream>
#include <fstream>
#include "mergesort.hpp"


int main() {

    std::ifstream file;
    file.open("numbers.txt");

    Mergesort<int, std::greater<int>> m(file);
    file.close();

    m.single_threaded();
    m.print();


    std::cin.get();
    return 0;
}
