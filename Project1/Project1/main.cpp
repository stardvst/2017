#include <algorithm>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>


void print_outliers(const std::vector<double>& v,
                    size_t start, size_t end,
                    double lowest, double highest) {
    for(; start <= end; ++start) {
        if(v[start] < lowest || v[start] > highest) {
            std::cout << v[start] << ' ';
        }
    }
}


int main() {

    std::ifstream file;
    file.open("numbers.txt");


    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        std::vector<double> v;

        double value;
        while(file >> value) {
            v.push_back(value);
        }

        std::sort(v.begin(), v.end());

        double q1 = v[v.size() / 4];
        double q3 = v[3 * v.size() / 4];

        double iqr = q3 - q1;

        double lowest = q1 - 1.5 * iqr;
        double highest = q3 + 1.5 * iqr;

        //print_outliers(v, 0, v.size() - 1, lowest, highest);

        std::thread t1(&print_outliers, v, 0,                       v.size() / 4,       lowest, highest);
        std::thread t2(&print_outliers, v, v.size() / 4 + 1,        v.size() / 2,       lowest, highest);
        std::thread t3(&print_outliers, v, v.size() / 2 + 1,        3 * v.size() / 4,   lowest, highest);
        std::thread t4(&print_outliers, v, 3 * v.size() / 4 + 1,    v.size() - 1,       lowest, highest);

        if(t1.joinable()) {
            t1.join();
        }
        if(t2.joinable()) {
            t2.join();
        }
        if(t3.joinable()) {
            t3.join();
        }
        if(t4.joinable()) {
            t4.join();
        }


        file.close();
    }

    std::cin.get();
    return 0;
}
