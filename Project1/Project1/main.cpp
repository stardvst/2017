#include <iostream>


class A {
public:
  static unsigned count;

  A() { ++count; }
  A(const A&) { ++count; }
  ~A() { --count; }
};

unsigned A::count = 0;


int main() {

  const int N = 100;
  
  A a[N]; // ctor
  char* apt = new char[N * sizeof(A)];

  for(int i = 0; i < N; ++i) {
    new (&apt[i])A(a[i]); // copy ctor
  }

  delete[] apt;

  std::cout << A::count;

  std::cin.get();
  return 0;
}