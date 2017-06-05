#include <iostream>


class A {
public:
    virtual void f() { std::cout << "A::f"; }
    A() { f(); }
    /* virtual */ ~A() { f(); }
};


class B : public A {
public:
    void f() override { std::cout << "B::f"; }
    B() { f(); }
    ~B() { f(); }
};

int main() {

    A* p = new B;
    p->f();
    delete p;

    std::cin.get();
    return 0;
}