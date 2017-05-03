#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <fstream>
#include <thread>
#include <vector>


#define MAX_THREADS 8

template<typename T>
class Mergesort {
public:
    Mergesort(std::ifstream&);
    void single_threaded();
    void multi_threaded();
    void print() const;
private:
    void single_threaded(std::vector<T>&, int, int);
    void multi_threaded(std::vector<T>&, int, int);
    void merge(std::vector<T>&, int, int, int);
private:
    std::vector<T> v;
    int threads;
};


template<typename T>
Mergesort<T>::Mergesort(std::ifstream& file) : threads(0) {
    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        T value;
        while(file >> value) {
            v.push_back(value);
        }
    }
}

template<typename T>
void Mergesort<T>::single_threaded() {
    std::vector<T> tmp(v.size());
    single_threaded(tmp, 0, static_cast<int>(v.size()) - 1);
}

template<typename T>
void Mergesort<T>::single_threaded(std::vector<T>& tmp, int low, int high) {
    if(low < high) {
        int mid = low + (high - low) / 2;
        single_threaded(tmp, low, mid);
        single_threaded(tmp, mid + 1, high);
        merge(tmp, low, mid, high);
    }
}

template<typename T>
void Mergesort<T>::multi_threaded() {
    std::vector<T> tmp(v.size());
    multi_threaded(tmp, 0, static_cast<int>(v.size()) - 1);
}

template<typename T>
void Mergesort<T>::multi_threaded(std::vector<T>& tmp, int low, int high) {
    if(high - low + 1 < 100 || threads >= MAX_THREADS) {
        single_threaded(tmp, low, high);
    } else {
        threads += 2;;

        int mid = low + (high - low) / 2;
        std::thread t1([&] { multi_threaded(tmp, low, mid); });
        std::thread t2([&] { multi_threaded(tmp, mid + 1, high); });
        if(t1.joinable()) {
            t1.join();
        }
        if(t2.joinable()) {
            t2.join();
        }
        merge(tmp, low, mid, high);
    }
}

template<typename T>
void Mergesort<T>::print() const {
    for(typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

template<typename T>
void Mergesort<T>::merge(std::vector<T>& tmp, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = low;

    while(i <= mid && j <= high) {
        if(v[i] <= v[j]) {
            tmp[k++] = v[i++];
        } else {
            tmp[k++] = v[j++];
        }
    }

    while(i <= mid) {
        tmp[k++] = v[i++];
    }
    while(j <= high) {
        tmp[k++] = v[j++];
    }

    for(int t = low; t <= high; ++t) {
        v[t] = tmp[t];
    }
}

#endif // !MERGESORT_HPP
