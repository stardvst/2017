#include <iostream>
#include <stdexcept>


class A {
public:
  A(int nn = 0) : n(nn) { std::cout << n; }
  ~A() { std::cout << n; }
private:
  int n;
};

int f(int n) {
  if(1 == n) {
    throw std::logic_error("0");
  }
  A l(n);
  return f(n - 1) * n / (n - 1);
}


int main() {

  try {
    int r = f(3);
    A a(r);
  } catch(const std::exception& e) {
    std::cout << e.what();
  }

  std::cin.get();
  return 0;
}
