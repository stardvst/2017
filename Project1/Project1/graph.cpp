#include <unordered_map>
#include <algorithm>
#include <vector>
#include <limits>
#include <queue>
#include <set>
#include "graph.hpp"


Graph::Graph(int v) : vertices(v), adjacents(vertices) {}

void Graph::add_edge(int vertex, int adjacent) {
    adjacents[vertex].insert(adjacent);
    adjacents[adjacent].insert(vertex);
}

bool Graph::is_connected() const {
    std::vector<bool> visited(vertices, false);
    BFS(visited);
    if(std::any_of(visited.begin(), visited.end(), [](bool v) { return !v; })) {
        return false;
    }
    return true;
}

int Graph::edge_connectivity() const {
    int k = std::numeric_limits<int>::max();
    int src = 0;

    for(int v = 1; v < vertices; ++v) {
        int dest = v;
        int flow = 0;
        Graph copy_graph = *this;

    FIND_DEST:
        while(copy_graph.path_exists(src, dest)) {
            std::vector<bool> visited(vertices, false);
            std::queue<int> queue;
            std::unordered_map<int, int> paths;

            queue.push(src);
            visited[src] = true;
            while(!queue.empty()) {
                int current = queue.front();
                queue.pop();
                
                std::set<int>::const_iterator end = copy_graph.adjacents[current].end();
                for(std::set<int>::const_iterator it = copy_graph.adjacents[current].begin(); it != end; ++it) {
                    int vertex = *it;
                    if(!visited[vertex]) {
                        paths[vertex] = current;
                        if(vertex != dest) {
                            visited[vertex] = true;
                            queue.push(vertex);
                        } else {
                            int v1 = dest;
                            while(v1 != src) {
                                int v2 = paths[v1];
                                copy_graph.adjacents[v1].erase(v2);
                                copy_graph.adjacents[v2].erase(v1);
                                v1 = v2;
                            }
                            ++flow;
                            goto FIND_DEST;
                        }
                    }
                }
            }
        }
        k = std::min(k, flow);
    }

    return k;
}


void Graph::BFS(std::vector<bool>& visited) const {
    std::queue<int> queue;
    queue.push(0);
    visited[0] = true;

    while(!queue.empty()) {
        int v = queue.front();
        queue.pop();

        std::set<int>::const_iterator end = adjacents[v].end();
        for(std::set<int>::const_iterator vertex = adjacents[v].begin(); vertex != end; ++vertex) {
            int current = *vertex;
            if(!visited[current]) {
                visited[current] = true;
                queue.push(current);
            }
        }
    }
}

bool Graph::path_exists(int src, int dest) const {
    std::vector<bool> visited(vertices, false);

    std::queue<int> queue;
    queue.push(src);

    while(!queue.empty()) {
        int v = queue.front();
        queue.pop();

        std::set<int>::const_iterator end = adjacents[v].end();
        for(std::set<int>::const_iterator vertex = adjacents[v].begin(); vertex != end; ++vertex) {
            int current = *vertex;
            if(current == dest) {
                return true;
            } else if(!visited[current]) {
                visited[current] = true;
                queue.push(current);
            }
        }
    }
    return false;
}
