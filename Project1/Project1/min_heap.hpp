#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <functional>
#include <vector>
#include "heap.hpp"


template<typename T>
struct Min_Heap : public Heap<T, std::less<T>> {
    template<typename T>
    friend class Median;

    void build_heap(const std::vector<T>&);
    void heapify(int);
    void insert(const T&);
    void extract();
    const T& minimum() const;
};


template<typename T>
void Min_Heap<T>::build_heap(const std::vector<T>& v) {
    return Heap<T, std::less<T>>::build_heap(v);
}

template<typename T>
void Min_Heap<T>::heapify(int i) {
    return Heap<T, std::less<T>>::heapify(i);
}

template<typename T>
void Min_Heap<T>::insert(const T& key) {
    return Heap<T, std::less<T>>::insert(key);
}

template<typename T>
void Min_Heap<T>::extract() {
    return Heap<T, std::less<T>>::extract();
}

template<typename T>
const T& Min_Heap<T>::minimum() const {
    return Heap<T, std::less<T>>::heap[0];
}

#endif // !MIN_HEAP_HPP
