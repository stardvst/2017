#include <iostream>


template<typename T, T t = T()>
class A {
private:
  template<bool b>
  struct B {
    static const int n = b ? 1 : 0;
  };

public:
  static const int value = B<(t > T())>::n - B<(t < T())>::n;
};


int main() {

  std::cout << A<int, -9>::value;
  std::cout << A<bool, true>::value;
  std::cout << A<char>::value;

  std::cin.get();
  return 0;
}
