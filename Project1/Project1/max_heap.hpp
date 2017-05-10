#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <functional>
#include <vector>
#include "heap.hpp"


template<typename T>
struct Max_Heap : public Heap<T, std::greater<T>> {
    void build_heap(const std::vector<T>&);
    void heapify(int);
    void insert(const T&);
    void extract();
    const T& maximum() const;
};


template<typename T>
void Max_Heap<T>::build_heap(const std::vector<T>& v) {
    return Heap<T, std::greater<T> >::build_heap(v);
}

template<typename T>
void Max_Heap<T>::heapify(int i) {
    return Heap<T, std::greater<T> >::heapify(i);
}

template<typename T>
void Max_Heap<T>::extract() {
    return Heap<T, std::greater<T> >::extract();
}

template<typename T>
void Max_Heap<T>::insert(const T& key) {
    return Heap<T, std::greater<T> >::insert(key);
}

template<typename T>
const T& Max_Heap<T>::maximum() const {
    return Heap<T, std::greater<T> >::heap[0];
}

#endif // !MAX_HEAP_HPP
