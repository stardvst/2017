#include <iostream>
#include <memory>

using namespace std;

struct A {
    A() { cout << "ctor"; }
    A(const A&) { cout << "copy ctor"; }
    ~A() { cout << "dtor"; }
};

void fn(unique_ptr<char> spc) {
    cout << *spc;
}

int main() {

    unique_ptr<char> up1(new char);
    *up1 = 'a';

    unique_ptr<char> up2 = move(up1);

    //fn(move(up2));

    up1.reset(new char);
    *up1 = 't';
    cout << *up1;
    up1.reset(new char);
    cout << *up1;


    std::cin.get();
    return 0;
}
