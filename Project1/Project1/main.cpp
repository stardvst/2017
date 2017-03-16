#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include "clustering.hpp"


int main() {

  int size = 0;
  while(size <= 0) {
    std::cout << "enter data size: ";
    std::cin >> size;
  }

  std::vector<int> data(size);

  for(int i = 0; i < size; ++i) {
    int element;
    std::cout << "data[" << i << "] = ";
    std::cin >> element;
    data[i] = element;
  }

  int distance = 0;
  while(distance <= 0) {
    std::cout << "enter max distance between cluster elements: ";
    std::cin >> distance;
  }

  std::sort(data.begin(), data.end());
  std::vector<std::list<int> > clusters = make_clusters(data, distance);


  // output data
  std::cout << "\n\ndata = [ ";
  for(int i = 0; i < size - 1; ++i) {
    std::cout << data[i] << ", ";
  }
  std::cout << data[size - 1] << " ]" << '\n';
  
  std::cout << "distance: " << distance << "\n\n";

  // output clusters
  std::cout << "clusters:\n";
   
  std::vector<std::list<int> >::const_iterator clusters_end = clusters.end();
  std::vector<std::list<int> >::const_iterator cluster = clusters.begin();
  
  for(int count = 0; cluster != clusters_end; ++cluster) {
    std::list<int>::const_iterator list_end = --(*cluster).end();
    std::cout << std::setw(20) << "cluster " << count << ": [ ";
    for(std::list<int>::const_iterator element = (*cluster).begin(); element != list_end; ++element) {
      std::cout << *element << ", ";
    }
    std::cout << *(--(*cluster).end()) << " ]\n";
    ++count;
  }
 

  std::cin.get();
  std::cin.get();
  return 0;
}
