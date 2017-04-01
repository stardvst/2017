#include <iostream>
#include <vector>


class A {
public:
  A() : i(0) {}
protected:
  int i;
};

class B {
public:
  B() : d(0.0) {}
protected:
  double d;
};

class C : public A, public B {
public:
  C() : c('a') {}
private:
  char c;
};


int main() {

  C cobj;
  A* ap = &cobj;
  B* bp = &cobj;

  const int a = (reinterpret_cast<char*>(ap) == reinterpret_cast<char*>(&cobj) ? 1 : 2);
  const int b = (bp == &cobj) ? 3 : 4;
  const int c = (reinterpret_cast<char*>(ap) == reinterpret_cast<char*>(bp)) ? 5 : 6;

  std::cout << a << b << c << std::endl;

  std::cin.get();
  return 0;
}
