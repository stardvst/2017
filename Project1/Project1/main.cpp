#include <iostream>

using namespace std;


int main() {

    int a = 1, b = 1;
    double r = 1.0, s = 1.0;
    //double e, f;

    auto ff = [](auto x, auto y) { return x + y; };
    auto f3 = [e = 2, f = 2]() {return e*f; };

    cout << ff(a, b) << '\n' << ff(r, s) << '\n' << f3();
    
    std::cin.get();
    return 0;
}
