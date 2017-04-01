#include <iostream>


template<typename T>
void kill(T*& t) {
  delete t;
  t = 0;
}

struct A {};


int main() {

  A* ptr = new A();
  kill(ptr);
  kill(ptr);


   std::cin.get();
  return 0;

  // ~A()
}
