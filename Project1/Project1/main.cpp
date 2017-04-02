#include <iostream>


class A {
public:
  explicit A(int nn = 0) : n(nn) {}
  
  A& operator=(const A& a) {
    n = a.n;
    ++assignment_calls;
    return *this;
  }

  static int assignment_calls;
private:
  int n;
};

int A::assignment_calls = 0;

A f(const A& a) { return a; }
A g(const A a) { return a; }

int main() {

  A a(3); // copy ctor
  A b = a; // copy ctor
  std::cout << A::assignment_calls;

  b = g(a); // operator=
  g(b); // copy ctor
  std::cout << A::assignment_calls;

  const A& c = f(b); // copy ctor
  std::cout << A::assignment_calls;


  std::cin.get();
  return 0;
}
