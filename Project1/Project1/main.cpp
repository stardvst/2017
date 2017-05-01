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

        int n = 0;
        while(n <= 0 || n > 100) {
            std::cout << "calculating nth percentile, n = ";
            std::cin >> n;
        }


        std::cout << "nth percentile: " << v[static_cast<int>(n * v.size() / 100) - 1];

        file.close();
    }

    std::cin.get();
    std::cin.get();
    return 0;
}