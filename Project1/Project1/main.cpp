#include <iostream>


struct A {
  virtual void f(int n) { std::cout << n << 1; }
  void f(int n) const   { std::cout << n; }

  virtual ~A() {}
};

struct B : A {
  void f(int n)       { std::cout << (n << 1); }
  void f(int n) const { std::cout << n + 1; }
};


int main() {

  const A a;
  B b;
  A& c = b;
  const A* d = &b;

  a.f(2);
  b.f(2);
  c.f(1);
  d->f(1);

  std::cin.get();
  return 0;
}
