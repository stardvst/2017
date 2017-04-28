#include <iostream>
#include "histogram.hpp"


int main() {

  int bin_size = 0;
  while(bin_size <= 0) {
    std::cout << "enter bin size: ";
    std::cin >> bin_size;
  }

  int anchor;
  std::cout << "enter anchor: ";
  std::cin >> anchor;


  Histogram h("numbers.txt", bin_size, anchor);
  h.create();
  std::cout << h;

  std::cin.ignore();
  std::cin.get();
  return 0;
}
