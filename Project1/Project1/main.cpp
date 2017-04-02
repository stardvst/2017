#include <iostream>
#include <set>


struct C {
  bool operator()(const int& a, const int& b) const {
    return a % 10 < b % 10;
  }
};


int main() {

  const int a[] = { 4,2,7,11,12,14,17,2 };
  const int count = sizeof(a) / sizeof(a[0]);

  std::set<int> x(a, a + count);
  std::cout << x.size();
  
  std::set<int, C> y(x.begin(), x.end());
  std::cout << y.size();

  std::cin.get();
  return 0;
}
