#include <iostream>
#include "graph.hpp"


int main() {

    int vertices;
    std::cout << "number of vertices: ";
    std::cin >> vertices;

    Graph graph(vertices);

    std::cout << "\nedges (ctrl+z to exit):\n";
    while(true) {
        int v1;
        int v2;
        std::cin >> v1;
        if(!std::cin.good()) {
            break;
        }
        std::cin >> v2;
        if(v1 >= 0 && v1 < vertices && v2 >= 0 && v2 < vertices) {
            graph.add_edge(v1, v2);
        }
    }

    std::cout << "\nis connected? " << std::boolalpha << graph.is_connected()
        << "\nedge connectivity: " << graph.edge_connectivity();

    std::cin.get();
    return 0;
}