#include <iostream>
#include "polynomial.hpp"


int main() {

  Polynomial p1;
  Polynomial p2;

  int number = 0, coeff, exp;
  while(number <= 0) {
    std::cout << "enter the number of terms in polynomial 1: ";
    std::cin >> number;
  }
  std::cout << '\n';
  for(int i = 0; i < number; ++i) {
    std::cout << "p1[" << i << "] coeff = ";
    std::cin >> coeff;
    std::cout << "p1[" << i << "] exp = ";
    std::cin >> exp;
    p1.add_term(coeff, exp);
    std::cout << '\n';
  }

  for(number = 0; number <= 0; ) {
    std::cout << "\nenter the number of terms in polynomial 2: ";
    std::cin >> number;
  }
  std::cout << '\n';
  for(int i = 0; i < number; ++i) {
    std::cout << "p2[" << i << "] coeff = ";
    std::cin >> coeff;
    std::cout << "p2[" << i << "] exp = ";
    std::cin >> exp;
    p2.add_term(coeff, exp);
    std::cout << '\n';
  }

  std::cout << "-----------------------\n";
  std::cout << "p1 = " << p1 << "\np2 = " << p2 << '\n';

  std::cout << "-----------------------\n";
  Polynomial p3 = p1 + p2;
  std::cout << "p1 + p2 = " << p3 << '\n';

  Polynomial p4 = p1 - p2;
  std::cout << "p1 - p2 = " << p4 << std::endl;


  std::cin.get();
  return 0;
}
