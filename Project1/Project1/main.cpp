#include <iostream>


struct B {};

struct A {
    A() { 
        ptr = new B[5]; 
        count = new int(1);
    }
    A(const A& a) {
        ptr = a.ptr;
        ++count;
    }
    ~A() {
        --count;
        if(count == 0) {
            delete[] ptr;
        }
    }
    B* ptr;
    int* count;
};

void f(A a) {
    // std::cout << *(a.count); // can't do this, only original object has access to count
    std::cout << 2;
}

int main() {

    A a;
    std::cout << *(a.count);
    f(a);
    std::cout << *(a.count);

    std::cin.get();
    return 0;
}
