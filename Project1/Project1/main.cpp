#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


int main() {

    std::ifstream file;
    file.open("numbers.txt");


    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        std::vector<int> v;

        int value;
        while(file >> value) {
            v.push_back(value);
        }

        std::sort(v.begin(), v.end());

        std::cout << "Q1: " << v[static_cast<int>(0.25 * v.size())]
            << "\nQ3: " << v[static_cast<int>(0.75 * v.size())];

        file.close();
    }


    std::cin.get();
    return 0;
}