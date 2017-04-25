#include <iostream>
#include "max_heap.hpp"
#include "min_heap.hpp"


int main() {

  std::vector<int> v = { 5,3,17,10,84,19,6,22,9 };

  
  Max_Heap<int> max_heap;
  max_heap.BUILD_MAX_HEAP(v);
  
  max_heap.INSERT(23);

  for(int i = 0; i < 10; ++i) {
    std::cout << "max: " << max_heap.MAXIMUM() << '\n';
    max_heap.EXTRACT_MAXIMUM();
  }

  std::cout << std::endl;

  Min_Heap<int> min_heap;
  min_heap.BUILD_MIN_HEAP(v);

  min_heap.INSERT(4);

  for(int i = 0; i < 10; ++i) {
    std::cout << "min: " << min_heap.MINIMUM() << '\n';
    min_heap.EXTRACT_MINIMUM();
  }


  std::cin.get();
  return 0;
}
