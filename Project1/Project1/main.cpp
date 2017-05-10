#include <iostream>
#include <fstream>
#include "red_black_tree.hpp"


int main() {

    std::ifstream file;
    file.open("numbers.txt");


    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        int size = 0;
        RedBlackTreeAug<int> rbt;

        int value;
        while(file >> value) {
            rbt.insert(value);
            ++size;
        }

        int n = 0;
        while(n <= 0 || n > 100) {
            std::cout << "calculating nth percentile, n = ";
            std::cin >> n;
        }

        std::cout << "nth percentile: " << order_stat_select(rbt, n * size / 100);

        file.close();
    }

    std::cin.get();
    std::cin.get();
    return 0;
}