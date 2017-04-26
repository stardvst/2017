#include <iostream>
#include <fstream>
#include <cmath>


int main() {

  std::ifstream infile;
  infile.open("numbers.txt");

  if(infile.is_open()) {

    int n = 0;
    double sum = 0;
    double sum_of_squares = 0;

    double value;
    while(infile >> value) {
      sum_of_squares += value * value;
      sum += value;
      ++n;
    }

    double mean = sum / n;

    std::cout << "standard deviation: " 
      << std::sqrt(sum_of_squares / (n - 1) - mean * mean);


    infile.close();
  }


  std::cin.get();
  return 0;
}
