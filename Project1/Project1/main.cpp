#include <iostream>



int main() {

  int num;
  std::cout << "num: ";
  std::cin >> num;
  
  
  short t = 0;
  while(num) {
    ++t;
    num &= num - 1; // remove last 1 bit
  }

  std::cout << "1's: " << t << std::endl;


  std::cin.get();
  std::cin.get();
}
