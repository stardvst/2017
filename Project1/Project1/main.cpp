#include <iostream>
#include <cstddef>


class A {
public:
  A() : x(0) {}

  static ptrdiff_t member_offset(const A& a) {
    const char *p = reinterpret_cast<const char*>(&a);
    const char *q = reinterpret_cast<const char*>(&a.x);
    return q - p;
  }
private:
  int x;
}; 

class B : public A {
public:
  B() : x('a') {}

  static int n;

  static ptrdiff_t member_offset(const B& b) {
    const char *p = reinterpret_cast<const char*>(&b);
    const char *q = reinterpret_cast<const char*>(&b.x);
    return q - p;
  }
private:
  char x;
};

int B::n = 1;


class C {
public:
  C() : x(0) {}
  virtual ~C() {}

  static ptrdiff_t member_offset(const C& c) {
    const char *p = reinterpret_cast<const char*>(&c);
    const char *q = reinterpret_cast<const char*>(&c.x);
    return q - p;
  }
private:
  int x;
};

int main() {

  A a;
  B b;
  C c;

  std::cout << ((A::member_offset(a) == 0) ? 0 : 1);
  std::cout << ((B::member_offset(b) == 0) ? 0 : 2);
  std::cout << ((A::member_offset(b) == 0) ? 0 : 3);
  std::cout << ((C::member_offset(c) == 0) ? 0 : 4);

  std::cin.get();
  return 0;
}
