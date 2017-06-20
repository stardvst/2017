#include <iostream>
#include <string>


bool is_perfect(int n) {
    int sum = 1;
    for(int i = 2; i <= n / 2; ++i) {
        if(n % i == 0) {
            sum += i;
        }
    }
    return n == sum;
}


int main() {

    std::cout << std::boolalpha << is_perfect(28);

    std::cin.get();
}
