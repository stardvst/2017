#include <iostream>
#include <string>


bool is_balanced(const std::string& s) {
    int count = 0;
    const std::size_t length = s.length();
    for(std::size_t i = 0; i < length; ++i) {
        if(s[i] == '(') {
            ++count;
        } else if(s[i] == ')') {
            --count;
        }
        if(count < 0) { // ) without opening brace
            return false;
        }
    }
    return !count;
}


int main() {

    std::string s = "())(";
    std::cout << std::boolalpha << is_balanced(s);

    std::cin.get();
}
