#include <iostream>
#include <thread>
#include <future>
#include <random>

using namespace std;

void consumer(future<char> &fx) {
    char c = fx.get();
    cout << c << endl;
}

int main() {

    promise<char> px;
    future<char> fx = px.get_future();

    thread t1(consumer, ref(fx));

    default_random_engine eng;
    uniform_int<char> dist { 'a', 'z' };

    px.set_value(dist(eng));

    t1.join();

    std::cin.get();
    return 0;
}
