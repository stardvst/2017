#include <iostream>


struct A {
  A() { std::cout << "A()"; }
  A(int) { std::cout << "A(int)"; }
  A& operator=(int) { std::cout << "="; return *this; }
};

class B {
public: 
  B() : m2(8) { m1 = 5; }
private:
  A m1;
  A m2;
};


int main() {

  B b;

  std::cin.get();
  return 0;
}