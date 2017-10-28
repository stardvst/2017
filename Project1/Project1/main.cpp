#include <iostream>
#include <thread>
#include <future>
#include <random>

using namespace std;

int func(int n) {
    return n;
}

struct fnc_ob {
    int n;
    fnc_ob(int i) : n(i) {}
    int operator()() { return n; }
};

int main() {

    future<int> f5 = async(func, 5);
    future<int> f10 = async(fnc_ob(10));
    auto f20 = async([](int i) {return i; }, 20);

    cout << f5.get() << endl;
    cout << f10.get() << endl;
    cout << f20.get() << endl;

    std::cin.get();
    return 0;
}
