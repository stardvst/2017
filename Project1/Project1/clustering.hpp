#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <vector>
#include <list>


class Clusters {
public:
  std::vector<std::list<int> > make_clusters(const std::vector<int>&);
private:
  int get_distance(const std::vector<int>&) const;
private:
  std::vector<std::list<int> > clusters;
};

#endif // !CLUSTERING_HPP
