#include <iostream>


class A {
public:
  A(int nn = 0) : n(nn) { std::cout << n; }
protected:
  int n;
};

class B : public A {
public:
  B(int param) : j(param), a(--j), b() { std::cout << j; }
private:
  int j;
  A a;
  A b;
  static A c;
};


int main() {

  B b(2);

  std::cin.get();
  return 0;
}

A B::c = 3;