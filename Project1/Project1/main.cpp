#include <iostream>

void print(int n) {
  if(n >= 10) {
    print(n / 10);
  }
  std::cout << n % 10;
}

int main() {

  print(156784);

  std::cin.get();
  return 0;
}