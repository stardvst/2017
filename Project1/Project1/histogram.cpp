#include <iostream>
#include <iomanip>
#include <utility>
#include <fstream>
#include <string>
#include <limits>
#include "histogram.hpp"


Histogram::Histogram(const std::string& file, int bc) : bin_count(bc) {
  infile.open(file);
  frequencies.resize(bin_count);
}

void Histogram::create() {
  if(infile.is_open() && infile.peek() != std::ifstream::traits_type::eof()) {
    
    std::pair<int, int> range = get_min_and_max();
    
    anchor = range.first;
    bin_size = static_cast<double>(range.second - anchor) / bin_count;

    infile.clear();
    infile.seekg(0, std::ios::beg);
    int value;
    while(infile >> value) {

      int index = (value - anchor) / bin_size;
      if(index == frequencies.size()) {
        frequencies.resize(bin_count + 1);
      }

      ++frequencies[index];
    }
  }
}

std::pair<int, int> Histogram::get_min_and_max() const {
  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();
  
  int value;
  while(infile >> value) {
    if(value < min) {
      min = value;
    } else if(value > max) {
      max = value;
    }
  }

  return std::make_pair(min, max);
}


std::ostream& operator<<(std::ostream& os, const Histogram& h) {
  const int size = static_cast<int>(h.frequencies.size());
  for(int i = 0; i < size; ++i) {
    os << '['
      << std::setprecision(2) << std::fixed << std::setiosflags(std::ios::showpoint)
      << std::setw(6) << h.anchor + h.bin_size * i << "; "
      << std::setw(5) << h.anchor + h.bin_size * (i + 1) << "]: ";

    int quantity = h.frequencies[i];
    for(int star = 0; star < quantity; ++star) {
      os << '*';
    }
    os << (quantity ? " (" : "(") << quantity << ')' << std::endl;
  }

  return os;
}