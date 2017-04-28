#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "histogram.hpp"


Histogram::Histogram(const std::string& file, int bs, int a) 
  : bin_size(bs), anchor(a) {
  infile.open(file);
}

void Histogram::create() {
  if(infile.is_open() && infile.peek() != std::ifstream::traits_type::eof()) {
    
    int bin_count = 0;

    int value;
    while(infile >> value) {
      if(value < anchor) {
        continue;
      }

      while(value > bin_count * bin_size + anchor) {
        ++bin_count;
      }

      if(bin_count > frequencies.size()) {
        frequencies.resize(bin_count);
      }

      int index = (value - anchor) / bin_size;
      if(index == frequencies.size()) {
        frequencies.resize(bin_count + 1);
      }

      ++frequencies[index];
    }
  }
}


std::ostream& operator<<(std::ostream& os, const Histogram& h) {
  const int size = static_cast<int>(h.frequencies.size());
  for(int i = 0; i < size; ++i) {
    os << '['
      << std::setw(3) << h.anchor + h.bin_size * i << "; "
      << std::setw(2) << h.anchor + h.bin_size * (i + 1) << "]: ";

    int quantity = h.frequencies[i];
    for(int star = 0; star < quantity; ++star) {
      os << '*';
    }
    os << (quantity ? " (" : ")") << quantity << ')' << std::endl;
  }

  return os;
}