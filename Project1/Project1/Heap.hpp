#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>


template<typename T>
struct Heap {
  std::vector<T> elements;
  int length;
  int heap_size;
};

#endif // !HEAP_HPP
