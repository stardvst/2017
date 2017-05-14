#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "red_black_tree.hpp"


int main() {

    std::ifstream file;
    file.open("input.txt");

    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        std::string line;
        RedBlackTree<std::string> rbt;

        std::getline(file, line);
        std::istringstream iss(line);
        while(iss >> line) {
            if(line != "{" && line != "}") {
                rbt.insert(line);
            }
        }


        std::string to_delete;
        std::cout << "\n\nenter values to delete (ctrl+z to exit)\n\nvalue: ";
        while(std::cin >> to_delete) {
            rbt.remove(to_delete);
            std::cout << "value: ";
        }
        std::cout << '\n';


        preorder(rbt);

        file.close();
    }

    std::cin.get();
    return 0;
}


