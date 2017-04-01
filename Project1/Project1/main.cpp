#include <iostream>
#include <memory>

// void f(std::auto_ptr<int>& a) - ok
void f(std::auto_ptr<int> a) {
  *a = 3;
}


int main() {

  std::auto_ptr<int> p(new int(0));
  f(p);
  std::cout << *p << std::endl;

  std::cin.get();
  return 0;
}
