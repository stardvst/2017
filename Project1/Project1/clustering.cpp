#include <iostream>
#include "clustering.hpp"


std::vector<std::list<int> > make_clusters(const std::vector<int>& data, int distance) {

  std::vector<std::list<int> > clusters;

  int count = 0;
  const size_t size = data.size();

  for(size_t i = 0; i < size; ++i) {
    clusters.push_back(std::list<int>());
    clusters[count].push_back(data[i]); // insert in list

    while(i + 1 < size && data[i + 1] <= data[i] + distance) {
      clusters[count].push_back(data[i + 1]);
      ++i;
    }

    ++count;
  }

  return clusters;
}