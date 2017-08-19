#include <iostream>

int reverse(int number) {
    int mirror = 0;
    while(number) {
        mirror = mirror * 10 + number % 10;
        number /= 10;
    }
    return mirror;
}

bool is_adam_number(int number) {
    const int mirror = reverse(number);
    return number * number == reverse(mirror * mirror);
}

int main() {
    std::cout << is_adam_number(12);
}