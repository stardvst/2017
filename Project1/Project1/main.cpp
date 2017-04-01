#include <iostream>


class A {
public:
  A(int ii = 0) : i(ii) { 
    std::cout << i; 
    ++i; 
  }
protected:
  int i;
};

class B : public A {
public:
  B() : a(new A[2]), x(++i) {
    std::cout << i;
  }
private:
  A x;
  A* a;
};


int main() {

  B b;

  std::cin.get();
  return 0;
}
