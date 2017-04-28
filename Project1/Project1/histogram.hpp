#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <fstream>
#include <iosfwd>
#include <string>
#include <vector>


class Histogram {
  friend std::ostream& operator<<(std::ostream&, const Histogram&);
public:
  Histogram(const std::string&, int, int);
  void create();
private:
  std::ifstream infile;
  int bin_size;
  int anchor;

  std::vector<int> frequencies;
};

#endif // !HISTOGRAM_HPP
