#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <tuple>


std::tuple<int, int, int> simultaneous_min_max(const std::vector<int>& v) {
    const std::size_t size = v.size();

    int min1 = v[0];
    int min2 = std::numeric_limits<int>::max();
    int max = min1;
    int i = 1;

    if(size % 2 == 0) {
        min1 = std::min(min1, v[1]);
        max = std::max(max, v[1]);
        min2 = max;
        i = 2;
    }

    for(; i < size - 1; i += 2) {
        int current_min = std::min(v[i], v[i + 1]);
        int current_max = std::max(v[i], v[i + 1]);
        if(current_min < min1) {
            if(min1 < min2) {
                min2 = min1;
            }
            min1 = current_min;
        } else if(current_min < min2) {
            min2 = current_min;
        }
        if(current_max > max) {
            max = current_max;
        }
    }

    return std::make_tuple(min1, min2, max);
}


int main() {

    std::vector<int> A { 3,0,1,5,4,7,10,8,9,12 };
    std::tuple<int, int, int> tuple = simultaneous_min_max(A);
    std::cout << "min: " << std::get<0>(tuple) << '\n'
        << "2nd min: " << std::get<1>(tuple) << '\n'
        << "max: " << std::get<2>(tuple) << std::endl;

    std::cin.get();
    return 0;
}