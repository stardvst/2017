#include <iostream>
#include <fstream>
#include "quicksort.hpp"


int main() {

    std::ifstream file;
    file.open("numbers.txt");

    Quicksort<int> q(file);
    file.close();

    q.multi_threaded();
    q.print();


    std::cin.get();
    return 0;
}
