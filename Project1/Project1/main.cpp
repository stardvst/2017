#include <iostream>
#include "histogram.hpp"


int main() {

  int bin_count = 0;
  while(bin_count <= 0) {
    std::cout << "enter bin count: ";
    std::cin >> bin_count;
  }


  Histogram h("numbers.txt", bin_count);
  h.create();
  std::cout << h;

  std::cin.ignore();
  std::cin.get();
  return 0;
}
