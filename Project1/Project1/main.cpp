#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>


int main() {

  std::ifstream infile;
  infile.open("pairs.txt");

  if(infile.is_open() && infile.peek() != std::ifstream::traits_type::eof()) {

    int n = 0; // # of pairs
    double x_sum = 0;
    double y_sum = 0;
    double xy_sum = 0;
    double x2_sum = 0;
    double y2_sum = 0;

    std::string line;

    while(std::getline(infile, line)) {
      std::istringstream iss(line);
      
      double x;
      double y;

      iss >> x;
      iss.ignore();
      iss >> y;

      double xy = x * y;
      double x2 = x * x;
      double y2 = y * y;

      x_sum += x;
      y_sum += y;

      xy_sum += xy;
      x2_sum += x2;
      y2_sum += y2;

      ++n;
    }

    std::cout << "correlation coefficient: " << std::setprecision(2) <<
      (n * xy_sum - x_sum * y_sum) /
      std::sqrt((n * x2_sum - x_sum * x_sum) * (n * y2_sum - y_sum * y_sum));
  }

  std::cin.get();
  return 0;
}
