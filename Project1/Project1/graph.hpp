#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <set>


class Graph {
public:
    Graph(int);

    void add_edge(int, int);
    bool is_connected() const;
    int edge_connectivity() const;
private:
    void BFS(std::vector<bool>&) const;
    bool path_exists(int, int) const;
private:
    const int vertices;
    std::vector<std::set<int> > adjacents;
};

#endif