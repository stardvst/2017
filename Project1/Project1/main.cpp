#include <iostream>
#include <vector>


int longest_0s(const std::vector<int>& v) {
    const std::size_t size = v.size();
    
    int max = 0;
    int current_max = 0;
    for(int i = 0; i < size; ++i) {
        if(v[i] == 0) {
            ++current_max;
        } else if(current_max > max) {
            max = current_max;
            current_max = 0;
        }
    }
    return max;
}

int main() {

    std::vector<int> v { 5,0,0,1,0,0,0,2 };
    std::cout << longest_0s(v);

    std::cin.get();
}