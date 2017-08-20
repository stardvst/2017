#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

std::vector<int> get_indexing(const std::vector<int> &v) {
    std::vector<int> tmp(v);
    std::sort(tmp.begin(), tmp.end());

    std::unordered_map<int, int> map;
    const int size = static_cast<int>(tmp.size());
    for(int i = 0; i < size; ++i) {
        map[tmp[i]] = i;
    }

    std::vector<int> result;
    for(std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        result.push_back(map[*it]);
    }

    return result;
}

int main() {
    
    std::vector<int> v = get_indexing({ 7, 9, 8, 1, 4 });
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    
    std::cin.get();
}