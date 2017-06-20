#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>


int find_2nd_max(const std::vector<int>& v) {
    const int size = static_cast<int>(v.size());
    
    int max1 = v[0];
    int max2 = std::numeric_limits<int>::min();
    int i = 1;
    
    if(!(size & 1)) {
        max1 = std::max(max1, v[1]);
        max2 = std::min(v[0], v[1]);
        i = 2;
    }

    for(; i < size - 1; i += 2) {
        int current_max = std::max(v[i], v[i + 1]);
        if(current_max > max1) {
            max2 = max1;
            max1 = current_max;
        }
    }

    return max2;
}

int main() {

    std::vector<int> v { 3,0,1,5,4,7,10,8,9,12 };
    std::cout << find_2nd_max(v);

    std::cin.get();
}