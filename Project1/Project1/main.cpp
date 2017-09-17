#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

void count_simple_paths(std::unordered_map<std::string, std::set<std::string>> &adj, const std::string &s, const std::string &t, int &count) {
    if(s == t) {
        ++count;
        return;
    }

    for(auto v : adj[s]) {
        count_simple_paths(adj, v, t, count);
    }
}

int main() {
    std::unordered_map<std::string, std::set<std::string>> adj_list;

    std::ifstream file("dag.txt");


    for(std::string line; std::getline(file, line); ) {
        std::string v;
        std::istringstream iss(line);
        iss >> v;

        iss.ignore(2);

        for(std::string adj; std::getline(iss, adj, ','); ) {
            adj_list[v].insert(adj);
        }
    }

    int count = 0;
    count_simple_paths(adj_list, "p", "v", count);
    std::cout << count << std::endl;

    std::cin.get();
    return 0;
}