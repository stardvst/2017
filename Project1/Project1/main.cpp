#include <iostream>


class A {
public:
  explicit A(int nn = 0) : n(nn) {}
  A(const A& a) : n(a.n) {
    ++copy_ctor_calls;
  }
public:
  static int copy_ctor_calls;
private:
  int n;
};

int A::copy_ctor_calls = 0;
A f(const A& a) { return a; }
A g(const A a) { return a; }

int main() {

  A a;
  A b = a, c(a);
  std::cout << A::copy_ctor_calls;

  b = g(c);
  std::cout << A::copy_ctor_calls;

  const A& d = f(c);
  std::cout << A::copy_ctor_calls;
  d;

   std::cin.get();
  return 0;
}
