#include <iostream>
#include <vector>


int sort_order(const std::vector<int>& v) {
    const std::size_t size = v.size();

    int asc = true;
    int desc = true;
    for(int i = 0; i < size - 1; ++i) {
        if(v[i] < v[i + 1]) {
            desc = false;
        } else if(v[i] > v[i + 1]) {
            asc = false;
        }
    }
    return asc ? 1 : desc ? -1 : 0;
}


int main() {

    std::vector<int> v { 0,1,1,5,7,8 };
    std::cout << sort_order(v);

    std::cin.get();
}
