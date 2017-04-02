#include <algorithm>
#include <iostream>
#include <list>


struct P {
  bool operator()(const int& n) const {
    return n % 3 == 0;
  }
};


int main() {

  const int a[] = { 5,2,6,1,13,9,19 };
  const int count = sizeof(a) / sizeof(a[0]);

  std::list<int> l(a, a + count);

  std::cout << l.size();
  std::remove_if(l.begin(), l.end(), P());
  std::cout << l.size();

  std::cin.get();
  return 0;
}
