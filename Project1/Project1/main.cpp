#include "singleton.h"

singleton *singleton::m_instance = nullptr;

int main() {
    
    singleton *m = singleton::get_instance();
    m->print();

}