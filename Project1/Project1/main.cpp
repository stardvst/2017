#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>


std::pair<int, int> simultaneous_min_max(const std::vector<int>& v) {
    const std::size_t size = v.size();
    
    int min = v[0];
    int max = min;
    int i = 1;

    if(size % 2 == 0) {
        min = std::min(min, v[1]);
        max = std::max(max, v[1]);
        i = 2;
    }

    for(; i < size - 2; i += 2) {
        int current_min = std::min(v[i], v[i + 1]);
        int current_max = std::max(v[i], v[i + 1]);
        if(current_min < min) {
            min = current_min;
        }
        if(current_max > max) {
            max = current_max;
        }
    }

    return std::make_pair(min, max);
}


int main() {

    std::vector<int> A { 3,1,6,8,7,5,3 };
    std::pair<int, int> pair = simultaneous_min_max(A);
    std::cout << "min: " << pair.first << '\n';
    std::cout << "max: " << pair.second << std::endl;
    
    std::cin.get();
    return 0;
}