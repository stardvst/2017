#include <functional>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <cassert>
#include <vector>


class A {
public:
  A() : size(sizeof(A)) {}
  virtual ~A() {}

  virtual void f() const { std::cout << 1; }

  static bool compare(const A* a, const A* b) {
    assert(a != 0);
    assert(b != 0);
    return a->size < b->size;
  }

protected:
  size_t size;
};

class B : public A {
public:
  B() : b(0) { size = sizeof(B); }
  virtual void f() const { std::cout << 2; }
private:
  char* b;
};

class C : public A {
public:
  C() { size = sizeof(C); }
  virtual void f() const { std::cout << 3; }
private:
  static int* c;
};

int* C::c = 0;

struct D {
  void operator()(A* a) const { delete a; }
};


int main() {

  std::cout << sizeof(A)  << " " << sizeof(B) << " " << sizeof(C) << "\n";

  typedef std::vector<A*> V;
  V v;
  v.push_back(new C);
  v.push_back(new B);
  v.push_back(new A);

  std::stable_sort(v.begin(), v.end(), A::compare);

  std::for_each(v.begin(), v.end(), std::mem_fun(&A::f));

  D d;
  std::for_each(v.begin(), v.end(), d);

  std::cin.get();
  return 0;
}
