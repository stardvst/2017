#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> accumulator = 0;

void func() {
    for(auto i = 0; i < 250; ++i)
        ++accumulator;
}

struct fnc_ob {
    void operator()() {
        for(auto i = 0; i < 250; ++i)
            ++accumulator;
    }
};

int main() {

    thread t1 { func };

    thread t2 { []() {
        for(auto i = 0; i < 250; ++i)
            ++accumulator;
    } };

    thread t3 { fnc_ob() };

    t1.join();
    t2.join();
    t3.join();

    cout << accumulator;

    std::cin.get();
    return 0;
}
