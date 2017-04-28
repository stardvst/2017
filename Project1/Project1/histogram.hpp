#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <fstream>
#include <utility>
#include <iosfwd>
#include <string>
#include <vector>


class Histogram {
  friend std::ostream& operator<<(std::ostream&, const Histogram&);
public:
  Histogram(const std::string&, int);
  void create();

private:
  std::pair<int, int> get_min_and_max() const;

private:
  mutable std::ifstream infile;
  int anchor;
  double bin_size;
  int bin_count;

  std::vector<int> frequencies;
};

#endif // !HISTOGRAM_HPP
