#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <limits>


template<typename T, typename C>
class Heap {
public:
    virtual ~Heap() = 0;
    virtual void build_heap(const std::vector<T>&);
    virtual void heapify(int);
    virtual void insert(const T&);
    virtual void extract();
private:
    virtual void change_key(int, const T&);
private:
    int PARENT(int i) const { return i % 2 ? i / 2 : i / 2 - 1; }
    int LEFT(int i) const { return  2 * i + 1; }
    int RIGHT(int i) const { return 2 * i + 2; }
protected:
    std::vector<T> heap;
};


template<typename T, typename C>
Heap<T, C>::~Heap() {}


template<typename T, typename C>
void Heap<T, C>::build_heap(const std::vector<T>& v) {
    heap = std::move(v);
    for(int i = static_cast<int>(v.size()) / 2 - 1; i >= 0; --i) {
        heapify(i);
    }
}

template<typename T, typename C>
void Heap<T, C>::heapify(int i) {
    C cmp;
    const size_t size = heap.size();
    while(true) {
        int left = LEFT(i);
        int right = RIGHT(i);
        int element = i;
        if(left < size && cmp(heap[left], heap[i])) {
            element = left;
        }
        if(right < size && cmp(heap[right], heap[element])) {
            element = right;
        }
        if(element == i) {
            return;
        }
        std::swap(heap[i], heap[element]);
        i = element;
    }
}

template<typename T, typename C>
void Heap<T, C>::insert(const T& value) {
    C cmp;
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if(cmp(min, max)) {
        heap.push_back(max);
    } else {
        heap.push_back(min);
    }
    change_key(static_cast<int>(heap.size()) - 1, value);
}

template<typename T, typename C>
void Heap<T, C>::extract() {
    const size_t size = heap.size();
    if(size > 0) {
        heap[0] = heap[size - 1];
        heap.erase(heap.begin() + size - 1);
        heapify(0);
    }
}

template<typename T, typename C>
void Heap<T, C>::change_key(int i, const T& key) {
    C cmp;
    const size_t size = heap.size();
    if(cmp(key, heap[size - 1])) {
        heap[size - 1] = key;
        while(i > 0 && cmp(heap[i], heap[PARENT(i)])) {
            std::swap(heap[PARENT(i)], heap[i]);
            i = PARENT(i);
        }
    }
}

#endif // !HEAP_HPP
