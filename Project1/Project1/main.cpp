#include <iostream>


class A {
public:
  A(int nn = 0) : n(nn) {}
  
  A(const A& a) : n(a.n) { ++copy_ctor_calls; }
  ~A() { ++dtor_calls; }

  static int copy_ctor_calls;
  static int dtor_calls;
private:
  int n;
};

int A::copy_ctor_calls = 0;
int A::dtor_calls = 0;


int main() {

  A* p = 0;

  {
    const A a = 2;
    p = new A[3];
    p[0] = a;
  }

  std::cout << A::copy_ctor_calls << A::dtor_calls;

  p[1] = A(1);
  p[2] = 2;

  delete[] p;

  std::cout << A::copy_ctor_calls << A::dtor_calls;

  std::cin.get();
  return 0;
}
