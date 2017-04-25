#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <vector>
#include <limits>


template<typename T>
class Max_Heap {
  friend class Median;
public:
  Max_Heap() {}
  void BUILD_MAX_HEAP(const std::vector<T>&);
  void MAX_HEAPIFY(int);
  const T& MAXIMUM() const;
  void EXTRACT_MAXIMUM();
  void INSERT(const T&);
  void INCREASE_KEY(int, const T&);
  void DELETE(int);
private:
  int PARENT(int i) const { return i % 2 ? i / 2 : i / 2 - 1; }
  int LEFT(int i) const { return  2 * i + 1; }
  int RIGHT(int i) const { return 2 * i + 2; }
private:
  std::vector<T> heap;
};


template<typename T>
void Max_Heap<T>::BUILD_MAX_HEAP(const std::vector<T>& v) {
  heap = v;

  for(int i = static_cast<int>(v.size()) / 2 - 1; i >= 0; --i) {
    MAX_HEAPIFY(i);
  }
}

template<typename T>
void Max_Heap<T>::MAX_HEAPIFY(int i) {
  const size_t size = heap.size();

  int left = LEFT(i);
  int right = RIGHT(i);
  int largest;
  if(left < size && heap[left] > heap[i]) {
    largest = left;
  } else {
    largest = i;
  }
  if(right < size && heap[right] > heap[largest]) {
    largest = right;
  }
  if(largest != i) {
    std::swap(heap[i], heap[largest]);
    MAX_HEAPIFY(largest);
  }
}

template<typename T>
const T& Max_Heap<T>::MAXIMUM() const {
  return heap[0];
}

template<typename T>
void Max_Heap<T>::EXTRACT_MAXIMUM() {
  const size_t size = heap.size();
  if(size < 1) {
    std::cerr << "heap underflow.\n";
  }
  heap[0] = heap[size - 1];
  heap.erase(heap.begin() + size - 1);
  MAX_HEAPIFY(0);
}

template<typename T>
void Max_Heap<T>::INSERT(const T& key) {
  heap.push_back(std::numeric_limits<T>::min());
  INCREASE_KEY(static_cast<int>(heap.size()) - 1, key);
}

template<typename T>
void Max_Heap<T>::INCREASE_KEY(int i, const T& key) {
  const size_t size = heap.size();
  if(key < heap[size - 1]) {
    std::cerr << "new key is smaller than current key.\n";
  }
  heap[size - 1] = key;
  while(i > 0 && heap[PARENT(i)] < heap[i]) {
    std::swap(heap[PARENT(i)], heap[i]);
    i = PARENT(i);
  }
}

template<typename T>
void Max_Heap<T>::DELETE(int i) {
  const size_t size = heap.size();
  if(heap[i] < heap[size - 1]) {
    INCREASE_KEY(i, heap[size - 1]);
    heap.erase(heap.begin() + size - 1);
  } else {
    heap[i] = heap[size - 1];
    heap.erase(heap.begin() + size - 1);
    MAX_HEAPIFY(i);
  }
}


#endif // !MAX_HEAP_HPP
