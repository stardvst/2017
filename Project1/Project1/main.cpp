#include <iostream>

using namespace std;

auto func(int x, int y) {
    return x + y;
}

int main() {

    int a = 1, b = 1;

    cout << func(a, b);
    
    std::cin.get();
    return 0;
}
