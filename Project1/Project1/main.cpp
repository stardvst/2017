#include "singleton.h"

singleton *singleton::m_instance = nullptr;
std::unordered_map<std::string, singleton *> singleton::m_registry;

singleton_subclass_1 *singleton_subclass_1::m_instance = nullptr;

int main() {
    
    singleton_subclass_1 *ss = singleton_subclass_1::get_instance();
    ss->print();

    singleton_subclass_1 *ss2 = singleton_subclass_1::get_instance();

    std::cout << std::boolalpha
        << "\nare both ptrs (=> both objects) the same? " << (ss == ss2)
        << std::endl;

    std::cin.get();
    return 0;
}