#include <iostream>
#include <string>


bool is_palindrome(const std::string& s) {
    const std::size_t length = s.length();
    for(std::size_t i = 0; i < length / 2; ++i) {
        if(s[i] != s[length - 1 - i]) {
            return false;
        }
    }
    return true;
}


int main() {

    std::string s = "abba";
    std::cout << std::boolalpha << is_palindrome(s);

    std::cin.get();
}
