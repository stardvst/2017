#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <functional>
#include <algorithm>
#include <fstream>
#include <thread>
#include <vector>


template<typename T, typename C = std::less<T>>
class Mergesort {
public:
    Mergesort(std::ifstream&);
    void single_threaded(C = C());
    void multi_threaded(C = C());
    void print() const;
private:
    void single_threaded(std::vector<T>&, int, int, C);
    void multi_threaded(std::vector<T>&, int, int, C);
    void merge(std::vector<T>&, int, int, int, C);
private:
    std::vector<T> v;
    int threads;
    const int max_threads;
};


template<typename T, typename C>
Mergesort<T, C>::Mergesort(std::ifstream& file)
    : threads(0), max_threads(std::thread::hardware_concurrency()) {

    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        T value;
        while(file >> value) {
            v.push_back(value);
        }
    }
}

template<typename T, typename C>
void Mergesort<T, C>::single_threaded(C cmp) {
    std::vector<T> tmp(v.size());
    single_threaded(tmp, 0, static_cast<int>(v.size()) - 1, cmp);
}

template<typename T, typename C>
void Mergesort<T, C>::single_threaded(std::vector<T>& tmp, int low, int high, C cmp) {
    int length = high - low + 1;
    for(int size = low + 1; size < length; size *= 2) {
        for(int left = low; left < length - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, length - 1);
            merge(tmp, left, mid, right, cmp);
        }
    }
}

template<typename T, typename C>
void Mergesort<T, C>::multi_threaded(C cmp) {
    std::vector<T> tmp(v.size());
    multi_threaded(tmp, 0, static_cast<int>(v.size()) - 1, cmp);
}

template<typename T, typename C>
void Mergesort<T, C>::multi_threaded(std::vector<T>& tmp, int low, int high, C cmp) {
    if(high - low + 1 <= v.size() / max_threads || threads >= max_threads) {
        single_threaded(tmp, low, high, cmp);
    } else {
        threads += 2;

        int mid = low + (high - low) / 2;
        std::thread t1([&] { multi_threaded(tmp, low, mid, cmp); });
        std::thread t2([&] { multi_threaded(tmp, mid + 1, high, cmp); });
        if(t1.joinable()) {
            t1.join();
        }
        if(t2.joinable()) {
            t2.join();
        }
        merge(tmp, low, mid, high, cmp);
    }
}

template<typename T, typename C>
void Mergesort<T, C>::print() const {
    for(typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

template<typename T, typename C>
void Mergesort<T, C>::merge(std::vector<T>& tmp, int low, int mid, int high, C cmp) {
    int i = low;
    int j = mid + 1;

    for(int k = low; k <= high; ++k) {
        tmp[k] = v[k];
    }

    for(int k = low; k <= high; ++k) {
        if(i > mid) {
            v[k] = tmp[j++];
        } else if(j > high) {
            v[k] = tmp[i++];
        } else if(cmp(tmp[j], tmp[i])) {
            v[k] = tmp[j++];
        } else {
            v[k] = tmp[i++];
        }
    }
}

#endif // !MERGESORT_HPP
