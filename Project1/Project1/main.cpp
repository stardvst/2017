#include <iostream>
#include <vector>


class A {
public:
  A(int nn = 2) : n(nn) {}
  ~A() { std::cout << n; }
protected:
  int n;
};

class B : public A {
public:
  B(int nn) : x(n + 1), a(nn) {}
  ~B() { std::cout << n; --n; }
private:
  A x;
  A a;
};


int main() {

  { B b(5); }

  std::cin.get();
  return 0;
}
