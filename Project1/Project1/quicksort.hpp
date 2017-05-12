#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <functional>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <thread>
#include <vector>
#include <stack>
#include <ctime>


template<typename T, typename C = std::less<T>>
class Quicksort {
public:
    Quicksort(std::ifstream&);
    void single_threaded(C = C());
    void multi_threaded(C = C());
    void print() const;
private:
    void single_threaded(int, int, C);
    void multi_threaded(int, int, C);
    int partition(int, int, C);
private:
    std::vector<T> v;
    int threads;
    const int max_threads;
};


template<typename T, typename C>
Quicksort<T, C>::Quicksort(std::ifstream& file) 
    : threads(0), max_threads(std::thread::hardware_concurrency()) {
    if(file.is_open()) {
        T value;
        while(file >> value) {
            v.push_back(value);
        }
    }
}

template<typename T, typename C>
void Quicksort<T, C>::single_threaded(C cmp) {
    single_threaded(0, static_cast<int>(v.size()) - 1, cmp);
}

template<typename T, typename C>
void Quicksort<T, C>::single_threaded(int low, int high, C cmp) {
    std::stack<T> stack;
    stack.push(low);
    stack.push(high);

    while(!stack.empty()) {
        high = stack.top();
        stack.pop();
        low = stack.top();
        stack.pop();

        int pivot = partition(low, high, cmp);

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

template<typename T, typename C>
void Quicksort<T, C>::multi_threaded(C cmp) {
    multi_threaded(0, static_cast<int>(v.size()) - 1, cmp);
}

template<typename T, typename C>
void Quicksort<T, C>::multi_threaded(int low, int high, C cmp) {
    if(low < high) {
        if(high - low + 1 <= v.size() / max_threads || threads >= max_threads) {
            single_threaded(low, high, cmp);
        } else {
            threads += 2;

            int q = partition(low, high, cmp);
            std::thread t1([&] { multi_threaded(low, q - 1, cmp); });
            std::thread t2([&] { multi_threaded(q + 1, high, cmp); });

            if(t1.joinable()) {
                t1.join();
            }
            if(t2.joinable()) {
                t2.join();
            }
        }
    }
}

template<typename T, typename C>
void Quicksort<T, C>::print() const {
    for(typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}


template<typename T, typename C>
int Quicksort<T, C>::partition(int low, int high, C cmp) {
    T pivot = v[high];
    int i = low - 1;

    for(int j = low; j < high; ++j) {
        if(cmp(v[j], pivot)) {
            std::swap(v[++i], v[j]);
        }
    }
    std::swap(v[i + 1], v[high]);
    return i + 1;
}

#endif // !QUICKSORT_HPP
