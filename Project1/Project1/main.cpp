#include <iostream>
#include <memory>

using namespace std;

struct A {
    A() { cout << "ctor"; }
    A(const A&) { cout << "copy ctor"; }
    ~A() { cout << "dtor"; }
};

void fn(shared_ptr<char> spc) {
    cout << spc.use_count();
}

int main() {

    shared_ptr<A> sp1(new A);
    //*sp1 = 'a';

    shared_ptr<A> sp2 = sp1;

    sp1.reset();

    /*sp2.reset();
    cout << sp1.use_count();
    cout << sp2.use_count();*/

    std::cin.get();
    return 0;
}
