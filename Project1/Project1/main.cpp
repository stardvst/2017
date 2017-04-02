#include <iostream>
#include <stdexcept>


class A {
  friend int g(const A&);
public:
  A(int nn = 0) : n(nn) {}
  
  int operator()(int i = 0) const { return n + i; }
  operator int() const { return n; }
private:
  int n;
};


// these functions are USELESS!!! they're for distracting

//int f(char c) { return c; } 
//int g(const A& a) { return a.n; }


int main() {

  A f(2), g(3);

  std::cout << f(1);
  std::cout << g(f);

  std::cin.get();
  return 0;
}
