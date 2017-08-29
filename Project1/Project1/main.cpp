#include <iostream>
#include <memory>

struct Base { virtual int value() const { return 1; } };
struct Derived : Base { int value() const { return 2; } };

//// don't do this
//int use_a_base(std::shared_ptr<Base> p) {
//    return p->value();
//}
//
//int main() {
//    auto ptr = std::make_shared<Derived>();
//    use_a_base(ptr);
//}

// pass a & to const
int use_a_base(const Base &p) {
    return p.value();
}

// pass a * to const
int use_a_base(const Base *p) {
    return p->value();
}

int main() {
    auto ptr = std::make_shared<Derived>();
    std::cout << use_a_base(*ptr.get()) << '\n';
    std::cout << use_a_base(ptr.get()) << '\n';
}
