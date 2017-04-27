#include <iostream>
#include <fstream>


int main() {

  std::ifstream infile;
  infile.open("numbers.txt");

  if(infile.is_open() && infile.peek() != std::ifstream::traits_type::eof()) {

    int n = 0;
    double mean = 0; // M1
    double M2 = 0;
    double M3 = 0;
    double M4 = 0;

    double value;
    while(infile >> value) {
      double delta;
      double delta_n;
      double delta_n2;

      int n1 = n;
      ++n;

      delta = value - mean;
      delta_n = delta / n;
      delta_n2 = delta_n * delta_n;

      double term1 = delta * delta_n * n1;

      mean += delta_n;
      M4 += term1 * delta_n2 * (n * n - 3 * n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3;
      M3 += term1 * delta_n * (n - 2) - 3 * delta_n * M2;
      M2 += term1;
    }

    std::cout << "kurtosis: " << (n * M4) / (M2 * M2) - 3;


    infile.close();
  }


  std::cin.get();
  return 0;
}
