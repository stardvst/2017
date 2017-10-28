#include <iostream>
#include <thread>
#include <future>
#include <random>

using namespace std;

int func(int n) {
    return n;
}

int main() {

    packaged_task<int(int)> f(func); // assign a function to p_t
    future<int /*ret val*/> r = f.get_future(); // link a future to ret val of p_t f

    thread t1(move(f), 9); // no copy ctor so it must be moved (to keep uniquness of p_t)
    cout << r.get() << endl;

    t1.join();

    std::cin.get();
    return 0;
}
