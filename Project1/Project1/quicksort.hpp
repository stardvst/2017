#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <fstream>
#include <utility>
#include <cstdlib>
#include <thread>
#include <vector>
#include <stack>
#include <ctime>


template<typename T>
class Quicksort {
public:
    Quicksort(std::ifstream&);
    void single_threaded();
    void multi_threaded();
    void print() const;
private:
    void single_threaded(int, int);
    void multi_threaded(int, int);
    void multi_threaded_iter(int, int);
    int partition(int, int);
private:
    std::vector<T> v;
    int threads;
    const int max_threads;
};


template<typename T>
Quicksort<T>::Quicksort(std::ifstream& file) 
    : threads(0), max_threads(std::thread::hardware_concurrency()) {
    if(file.is_open()) {
        T value;
        while(file >> value) {
            v.push_back(value);
        }
    }
}

template<typename T>
void Quicksort<T>::single_threaded() {
    single_threaded(0, static_cast<int>(v.size()) - 1);
}

template<typename T>
void Quicksort<T>::single_threaded(int low, int high) {
    std::stack<T> stack;
    stack.push(low);
    stack.push(high);

    while(!stack.empty()) {
        high = stack.top();
        stack.pop();
        low = stack.top();
        stack.pop();

        int pivot = partition(low, high);

        if(pivot - 1 > low) {
            stack.push(low);
            stack.push(pivot - 1);
        }
        if(pivot + 1 < high) {
            stack.push(pivot + 1);
            stack.push(high);
        }
    }
}

template<typename T>
void Quicksort<T>::multi_threaded() {
    multi_threaded(0, static_cast<int>(v.size()) - 1);
}

template<typename T>
void Quicksort<T>::multi_threaded(int low, int high) {
    if(low < high) {
        if(high - low + 1 <= v.size() / max_threads || threads >= max_threads) {
            single_threaded(low, high);
        } else {
            threads += 2;

            int q = partition(low, high);
            std::thread t1([&] { multi_threaded(low, q - 1); });
            std::thread t2([&] { multi_threaded(q + 1, high); });

            if(t1.joinable()) {
                t1.join();
            }
            if(t2.joinable()) {
                t2.join();
            }
        }
    }
}

template<typename T>
void Quicksort<T>::print() const {
    for(typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}


template<typename T>
int Quicksort<T>::partition(int low, int high) {
    T pivot = v[high];
    int i = low - 1;

    for(int j = low; j < high; ++j) {
        if(v[j] <= pivot) {
            std::swap(v[++i], v[j]);
        }
    }
    std::swap(v[i + 1], v[high]);
    return i + 1;
}

#endif // !QUICKSORT_HPP
