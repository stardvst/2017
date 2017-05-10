#ifndef MEDIAN_HPP
#define MEDIAN_HPP

#include <fstream>
#include <memory>
#include <string>
#include <cmath>
#include "max_heap.hpp"
#include "min_heap.hpp"


template<typename T>
class Median {
public:
    Median(const std::string&);
    T get() const;
private:
    void build_heaps() const;
private:
    mutable std::ifstream infile;
    mutable std::unique_ptr<Max_Heap<T> > max_heap;
    mutable std::unique_ptr<Min_Heap<T> > min_heap;
};


template<typename T>
Median<T>::Median(const std::string& file) : infile(file),
max_heap(std::make_unique<Max_Heap<T> >()),
min_heap(std::make_unique<Min_Heap<T> >()) {}


template<typename T>
T Median<T>::get() const {
    build_heaps();

    const size_t max_heap_size = max_heap->heap.size();
    const size_t min_heap_size = min_heap->heap.size();

    if(max_heap_size == min_heap_size || max_heap_size > min_heap_size) {
        return max_heap->maximum();
    }
    return min_heap->minimum();
}

template<typename T>
void Median<T>::build_heaps() const {
    T value;
    while(infile >> value) {
        max_heap->insert(value);

        int max_heap_size = static_cast<int>(max_heap->heap.size());
        int min_heap_size = static_cast<int>(min_heap->heap.size());

        if((max_heap_size - min_heap_size > 1) ||
            (min_heap_size != 0 && max_heap->maximum() > min_heap->minimum())) {
            min_heap->insert(max_heap->maximum());
            max_heap->extract();
        }

        max_heap_size = static_cast<int>(max_heap->heap.size());
        min_heap_size = static_cast<int>(min_heap->heap.size());

        if(min_heap_size != 0 && (min_heap_size - max_heap_size) > 1) {
            max_heap->insert(min_heap->minimum());
            min_heap->extract();
        }
    }

}


#endif // !MEDIAN_HPP
