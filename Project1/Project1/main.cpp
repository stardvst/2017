#include "singleton.h"

// base singleton's static members need to be defined
singleton *singleton::m_instance = nullptr;
std::unordered_map<std::string, singleton *> singleton::m_registry;

// subclass instances need to be defined
singleton_subclass_1 *singleton_subclass_1::m_instance = nullptr;
singleton_subclass_2 *singleton_subclass_2::m_instance = nullptr;

int main() {

    singleton_subclass_1 *ss1 = singleton_subclass_1::get_instance();
    ss1->print_until_4();

    singleton_subclass_2 *ss2 = singleton_subclass_2::get_instance();
    ss2->print_until_9();

    singleton_subclass_1 *ss1_2 = singleton_subclass_1::get_instance();
    singleton_subclass_2 *ss2_2 = singleton_subclass_2::get_instance();

    std::cout << std::boolalpha
        << "\nare second ptrs of each subclasses the same as the first ptr?\n"
        << "subclass1: " << (ss1 == ss1_2)
        << "\nsubclass2: " << (ss2 == ss2_2)
        << std::endl;

    std::cin.get();
    return 0;
}