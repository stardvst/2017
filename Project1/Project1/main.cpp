#include <algorithm>
#include <iostream>
#include <vector>
#include <list>


class Int {
public:
  Int(int ii = 0) : i(ii) {}

  Int& operator=(const Int& a) {
    this->i = a.i;
    ++assignments;
    return *this;
  }

  bool operator<(const Int& a) const { return this->i == a.i; }

  static int get_assignments() { return assignments; }
private:
  int i;
  static int assignments;
};

int Int::assignments = 0;


int main() {

  std::list<Int> l;
  l.push_back(Int(3));
  l.push_back(Int(1));
  l.sort();

  std::cout << Int::get_assignments();

  std::vector<Int> v;
  v.push_back(Int(2));
  v.push_back(Int(1));
  std::sort(v.begin(), v.end());

  std::cout << Int::get_assignments();

  std::cin.get();
  return 0;
}
