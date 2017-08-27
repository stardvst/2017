#include <string>

struct S {
    S(std::string s) : m_s(std::move(s)) {}
    std::string m_s;
};

int main() {

    // copy the string
    for(int i = 0; i < 10000000; ++i) {
        std::string s = std::string("a not very short string") + "b";
        S o(s);
    }

    // move the string: 29% more efficient, 32% smaller binary
    for(int i = 0; i < 10000000; ++i) {
        std::string s = std::string("a not very short string") + "b";
        S o(std::move(s));
    }

    // CONSTRUCT IN PLACE!!! +2% efficient
    for(int i = 0; i < 10000000; ++i) {
        S o("a not very short string") + "b");
    }

}