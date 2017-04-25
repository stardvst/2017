#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <vector>
#include <memory>
#include <limits>
#include "Heap.hpp"


template<typename T>
class Min_Heap {
public:
  Min_Heap();
  void BUILD_MIN_HEAP(const std::vector<T>&);
  void MIN_HEAPIFY(int);
  const T& MINIMUM() const;
  void EXTRACT_MINIMUM();
  void INSERT(const T&);
  void DECREASE_KEY(int, const T&);
private:
  int PARENT(int i) const { return i % 2 ? i / 2 : i / 2 - 1; }
  int LEFT(int i) const { return  2 * i + 1; }
  int RIGHT(int i) const { return 2 * i + 2; }
private:
  std::unique_ptr<Heap<T> > heap;
};


template<typename T>
Min_Heap<T>::Min_Heap() {
  heap = std::make_unique<Heap<T> >();
}

template<typename T>
void Min_Heap<T>::BUILD_MIN_HEAP(const std::vector<T>& v) {
  heap->elements = std::move(v);
  heap->length = static_cast<int>(v.size());
  heap->heap_size = static_cast<int>(v.size());

  for(int i = static_cast<int>(v.size()) / 2 - 1; i >= 0; --i) {
    MIN_HEAPIFY(i);
  }
}

template<typename T>
void Min_Heap<T>::MIN_HEAPIFY(int i) {
  int left = LEFT(i);
  int right = RIGHT(i);
  int smallest;
  if(left < heap->heap_size && heap->elements[left] < heap->elements[i]) {
    smallest = left;
  } else {
    smallest = i;
  }
  if(right < heap->heap_size && heap->elements[right] < heap->elements[smallest]) {
    smallest = right;
  }
  if(smallest != i) {
    std::swap(heap->elements[i], heap->elements[smallest]);
    MIN_HEAPIFY(smallest);
  }
}

template<typename T>
const T& Min_Heap<T>::MINIMUM() const {
  return heap->elements[0];
}

template<typename T>
void Min_Heap<T>::EXTRACT_MINIMUM() {
  if(heap->heap_size < 1) {
    std::cerr << "heap underflow.\n";
  }
  heap->elements[0] = heap->elements[heap->heap_size - 1];
  heap->elements.erase(heap->elements.begin() + heap->heap_size - 1);
  --heap->heap_size;
  MIN_HEAPIFY(0);
}

template<typename T>
void Min_Heap<T>::INSERT(const T& key) {
  ++heap->length;
  ++heap->heap_size;
  heap->elements.push_back(std::numeric_limits<T>::max());
  DECREASE_KEY(heap->heap_size - 1, key);
}

template<typename T>
void Min_Heap<T>::DECREASE_KEY(int i, const T& key) {
  if(key > heap->elements[heap->heap_size - 1]) {
    std::cerr << "new key is larger than current key.\n";
  }
  heap->elements[heap->heap_size - 1] = key;
  while(i > 0 && heap->elements[PARENT(i)] > heap->elements[i]) {
    std::swap(heap->elements[PARENT(i)], heap->elements[i]);
    i = PARENT(i);
  }
}


#endif // !MIN_HEAP_HPP
