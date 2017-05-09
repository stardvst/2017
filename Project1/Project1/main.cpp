#include <iostream>
#include "red_black_tree.hpp"


int main() {

    RedBlackTree<int> rbt;

    int value;
    std::cout << "enter red-black tree keys (ctrl+z to exit)...\n\nkey: ";
    while(std::cin >> value) {
        rbt.insert(value);
        std::cout << "key: ";
    }

    std::cout << "\n\ttree: ";
    rbt.inorder();

    std::cin.clear();


    std::cout << "\n\nenter keys to delete (ctrl+z to exit)...\n\nkey: ";
    while(std::cin >> value) {
        if(!rbt.empty()) {
            rbt.remove(value);
            std::cout << "key: ";
        } else {
            std::cout << "\n\ttree is now empty.\n";
            break;
        }
    }

    if(!rbt.empty()) {
        std::cout << "\n\ttree: ";
        rbt.inorder();
    }


    std::cin.get();
    return 0;
}