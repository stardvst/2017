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

        std::cout << "Q1: " << order_stat_select(rbt, size / 4)
            << "\nQ3: " << order_stat_select(rbt, 3 * size / 4); 

        file.close();
    }

    std::cin.get();
    return 0;
}