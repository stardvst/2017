#include <iostream>


class A {
public:
  A(int nn = 2) : n(nn) {}

  int get_n() const { return n; }
  void set_n(int nn) { n = nn; }
private:
  int n;
};

class B {
public:
  B(char cc = 'a') : c(cc) {}

  char get_c() const { return c; }
  void set_c(char cc) { c = cc; }
private:
  char c;
};

class C : virtual public A, public B {};
class D : virtual public A, public B {};
class E : public C, public D {};


int main() {

  E e;
  C& c = e;
  D& d = e;

  std::cout << c.get_c() << d.get_n();

  c.set_n(3);
  d.set_c('b');

  std::cout << c.get_c() << d.get_n();

  std::cin.get();
  return 0;
}
