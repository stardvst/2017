#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <vector>
#include <memory>
#include <limits>
#include "Heap.hpp"


template<typename T>
class Max_Heap {
public:
  Max_Heap();
  void BUILD_MAX_HEAP(const std::vector<T>&);
  void MAX_HEAPIFY(int);
  const T& MAXIMUM() const;
  void EXTRACT_MAXIMUM();
  void INSERT(const T&);
  void INCREASE_KEY(int, const T&);
private:
  int PARENT(int i) const { return i % 2 ? i / 2 : i / 2 - 1; }
  int LEFT(int i) const { return  2 * i + 1; }
  int RIGHT(int i) const { return 2 * i + 2; }
private:
  std::unique_ptr<Heap<T> > heap;
};


template<typename T>
Max_Heap<T>::Max_Heap() {
  heap = std::make_unique<Heap<T> >();
}

template<typename T>
void Max_Heap<T>::BUILD_MAX_HEAP(const std::vector<T>& v) {
  heap->elements = std::move(v);
  heap->length = static_cast<int>(v.size());
  heap->heap_size = static_cast<int>(v.size());

  for(int i = static_cast<int>(v.size()) / 2 - 1; i >= 0; --i) {
    MAX_HEAPIFY(i);
  }
}

template<typename T>
void Max_Heap<T>::MAX_HEAPIFY(int i) {
  int left = LEFT(i);
  int right = RIGHT(i);
  int largest;
  if(left < heap->heap_size && heap->elements[left] > heap->elements[i]) {
    largest = left;
  } else {
    largest = i;
  }
  if(right < heap->heap_size && heap->elements[right] > heap->elements[largest]) {
    largest = right;
  }
  if(largest != i) {
    std::swap(heap->elements[i], heap->elements[largest]);
    MAX_HEAPIFY(largest);
  }
}

template<typename T>
const T& Max_Heap<T>::MAXIMUM() const {
  return heap->elements[0];
}

template<typename T>
void Max_Heap<T>::EXTRACT_MAXIMUM() {
  if(heap->heap_size < 1) {
    std::cerr << "heap underflow.\n";
  }
  heap->elements[0] = heap->elements[heap->heap_size - 1];
  heap->elements.erase(heap->elements.begin() + heap->heap_size - 1);
  --heap->heap_size;
  MAX_HEAPIFY(0);
}

template<typename T>
void Max_Heap<T>::INSERT(const T& key) {
  ++heap->length;
  ++heap->heap_size;
  heap->elements.push_back(std::numeric_limits<T>::min());
  INCREASE_KEY(heap->heap_size - 1, key);
}

template<typename T>
void Max_Heap<T>::INCREASE_KEY(int i, const T& key) {
  if(key < heap->elements[heap->heap_size - 1]) {
    std::cerr << "new key is smaller than current key.\n";
  }
  heap->elements[heap->heap_size - 1] = key;
  while(i > 0 && heap->elements[PARENT(i)] < heap->elements[i]) {
    std::swap(heap->elements[PARENT(i)], heap->elements[i]);
    i = PARENT(i);
  }
}


#endif // !MAX_HEAP_HPP
