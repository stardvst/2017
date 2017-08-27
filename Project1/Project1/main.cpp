#include <iostream>

// problems: 
// 1. move construction/assignment is disabled since we have v dtor
// 2. virtual ~Derived() is useless (it's virtual anyways)
struct Base {
    virtual ~Base() = default;
    virtual void do_a_thing() = 0;
};

struct Derived : Base {
    virtual ~Derived() = default;
    void do_a_thing() override {}
};

// correct: 10% faster
// Derived objects will have copy/move construction/assignment enabled for them
struct Base {
    Base() = default;
    virtual ~Base() = default;
    
    Base(const Base &) = default;
    Base& operator=(const Base &) = default;
    
    Base(Base &&) = default;
    Base& operator=(Base &&) = default;

    virtual void do_a_thing() = 0;
};

struct Derived : Base {
    void do_a_thing() override {}
};

int main() {
    
    std::cin.get();
}