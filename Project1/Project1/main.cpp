#include <iostream>
#include "max_heap.hpp"
#include "min_heap.hpp"


int main() {

    std::vector<int> v;

    int value;
    std::cout << "enter heap elements (ctrl+d to exit)...\n\nvalue: ";
    while(std::cin >> value) {
        v.push_back(value);
        std::cout << "value: ";
    }


    Max_Heap<int> max_heap;
    max_heap.build_heap(v);

    const size_t size = v.size();

    std::cout << "\n\nextracting max elements from max-heap...\n";
    for(size_t i = 0; i < v.size(); ++i) {
        std::cout << "current max: " << max_heap.maximum() << '\n';
        max_heap.extract();
    }

    Min_Heap<int> min_heap;
    min_heap.build_heap(v);

    std::cout << "\n\nextracting min elements from min-heap...\n";
    for(size_t i = 0; i < size; ++i) {
        std::cout << "current min: " << min_heap.minimum() << '\n';
        min_heap.extract();
    }


    std::cin.get();
    std::cin.get();
    return 0;
}