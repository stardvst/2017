#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <list>
#include "clustering.hpp"


int main() {

  std::ifstream infile("data.txt");
  std::vector<int> data;

  int current;
  while(infile >> current) {
    data.push_back(current);
  }

  infile.close();


  std::sort(data.begin(), data.end());
  Clusters c;
  std::vector<std::list<int> > clusters = c.make_clusters(data);

  std::ofstream outfile("clusters.txt", std::ios::trunc);

  std::vector<std::list<int> >::const_iterator cluster = clusters.begin();
  std::vector<std::list<int> >::const_iterator clusters_end = clusters.end();

  for(int count = 0; cluster != clusters_end; ++cluster) {
    std::list<int>::const_iterator list_end = --(*cluster).end();
    outfile << "[ ";
    for(std::list<int>::const_iterator element = (*cluster).begin(); element != list_end; ++element) {
      outfile << *element << ", ";
    }
    outfile << *(--(*cluster).end()) << " ]\n";
    ++count;
  }

  outfile.close();


  std::cout << "see \"clusters.txt\" for the result";

  std::cin.get();
  return 0;
}
