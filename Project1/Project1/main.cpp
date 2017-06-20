#include <iostream>
#include <vector>


int count_ones(int start, const std::vector<int>& v) {
    if(start < v.size()) {
        return (v[start] == 1) + count_ones(start + 1, v);
    }
    return 0;
}


int main() {

    std::vector<int> v { 0,1,1,5,7,8,1 };
    std::cout << count_ones(0, v);

    std::cin.get();
}
