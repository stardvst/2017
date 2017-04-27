#include <iostream>
#include <fstream>
#include <cmath>


int main() {

  std::ifstream infile;
  infile.open("numbers.txt");

  if(infile.is_open() && infile.peek() != std::ifstream::traits_type::eof()) {

    int n = 0;
    double mean = 0; // M1
    double M2 = 0;
    double M3 = 0;

    double value;
    while(infile >> value) {
      double delta;
      double delta_n;

      int n1 = n;
      ++n;

      delta = value - mean;
      delta_n = delta / n;

      double term1 = delta * delta_n * n1;

      mean += delta_n;
      M3 += term1 * delta_n * (n - 2) - 3 * delta_n * M2;
      M2 += term1;
    }

    std::cout << "kurtosis: " << (std::sqrt(n) * M3) / std::pow(M2, 1.5);


    infile.close();
  }


  std::cin.get();
  return 0;
}
