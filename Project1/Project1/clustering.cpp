#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include "clustering.hpp"


std::vector<std::list<int> > Clusters::make_clusters(const std::vector<int>& data) {

  int count = 0;
  const size_t size = data.size();
  int distance = get_distance(data);

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

int Clusters::get_distance(const std::vector<int>& data) const {

  std::vector<int> distances;
  const size_t size = data.size() - 1;

  for(size_t i = 0; i < size; ++i) {
    distances.push_back(data[i + 1] - data[i]);
  }

  std::nth_element(distances.begin(), 
                   distances.begin() + distances.size() / 2, 
                   distances.end()); 
  return distances[distances.size() / 2]; // returns the median
}
