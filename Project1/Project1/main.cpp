#include <functional>
#include <iostream>
#include <fstream>
#include "quicksort.hpp"


int main() {

    std::ifstream file;
    file.open("numbers.txt");

    Quicksort<int, std::greater<int>> q(file);
    file.close();

    q.single_threaded();
    q.print();


    std::cin.get();
    return 0;
}
