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

    thread t1 { []() {
        cout << this_thread::get_id() << endl;
        cout << "yield: ";
        this_thread::yield();
        cout << "done." << endl << "sleep for 500 ms: ";
        this_thread::sleep_for(chrono::milliseconds { 500 });
        cout << "done." << endl << "sleep until a time from now() + 5 seconds: ";
        this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
        cout << "done." << endl;
    } };

    t1.join();

    cout << "t1 join complete." << endl;

    std::cin.get();
    return 0;
}
