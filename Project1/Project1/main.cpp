#include <iostream>
#include <fstream>
#include "mergesort.hpp"


int main() {

    std::ifstream file;
    file.open("numbers.txt");

    Mergesort<int> m(file);
    file.close();

    m.multi_threaded();
    m.print();


    std::cin.get();
    return 0;
}
