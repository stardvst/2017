#include "singleton.h"

singleton *singleton::m_instance = nullptr;

int main() {
    
    singleton *s = singleton::get_instance();
    s->print();

    singleton *s2 = singleton::get_instance();

    std::cout << std::boolalpha
        << "\nare two ptrs equal? " << (s == s2)
        << "\nare two objects equal? " << (*s == *s2) << std::endl;

    std::cin.get();
    return 0;
}