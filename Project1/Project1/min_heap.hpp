#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <vector>
#include <limits>


template<typename T>
class Min_Heap {
  template<typename U>
  friend class Median;
public:
  Min_Heap() {}
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
  std::vector<T> heap;
};


template<typename T>
void Min_Heap<T>::MIN_HEAPIFY(int i) {
  const size_t size = heap.size();

  int left = LEFT(i);
  int right = RIGHT(i);
  int smallest;
  if(left < size && heap[left] < heap[i]) {
    smallest = left;
  } else {
    smallest = i;
  }
  if(right < size && heap[right] < heap[smallest]) {
    smallest = right;
  }
  if(smallest != i) {
    std::swap(heap[i], heap[smallest]);
    MIN_HEAPIFY(smallest);
  }
}

template<typename T>
const T& Min_Heap<T>::MINIMUM() const {
  return heap[0];
}

template<typename T>
void Min_Heap<T>::EXTRACT_MINIMUM() {
  const size_t size = heap.size();
  if(size > 0) {
    heap[0] = heap[size - 1];
    heap.erase(heap.begin() + size - 1);
    MIN_HEAPIFY(0);
  }
}

template<typename T>
void Min_Heap<T>::INSERT(const T& key) {
  heap.push_back(std::numeric_limits<T>::max());
  DECREASE_KEY(static_cast<int>(heap.size()) - 1, key);
}

template<typename T>
void Min_Heap<T>::DECREASE_KEY(int i, const T& key) {
  const size_t size = heap.size();
  if(key < heap[size - 1]) {
    heap[size - 1] = key;
    while(i > 0 && heap[PARENT(i)] > heap[i]) {
      std::swap(heap[PARENT(i)], heap[i]);
      i = PARENT(i);
    }
  }
}


#endif // !MIN_HEAP_HPP
