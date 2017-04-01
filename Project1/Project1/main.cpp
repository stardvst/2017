#include <iostream>


int main() {

  enum Colors {
    red,
    blue,
    white = 5,
    yellow,
    green,
    pink
  };

  Colors color = green;
  printf("%d", color);

  std::cin.get();
  return 0;
}
