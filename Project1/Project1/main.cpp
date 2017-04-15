#include <iostream>
#include "Binary_tree.hpp"
#include "Node.hpp"


int main() {

  int size = 0;
  while(size <= 0) {
    std::cout << "Enter the number of nodes: ";
    std::cin >> size;
  }

  Element<char>* elements = new Element<char>[size];  

  for(int i = 0; i < size; ++i) {
    std::cout << "elements[" << i << "] = ";
    std::cin >> elements[i].value;
    std::cin >> elements[i].left;
    std::cin >> elements[i].right;
  }


  Binary_tree<char> tree(elements, size);

  std::cout << "\nlevelorder: ";
  tree.levelorder();

  std::cout << "\n\n# of leaves: " << tree.leaf_count()
    << "\ntree height: " << tree.height()
    << "\ntree width: " << tree.width();


  std::cin.get();
  std::cin.get();
  return 0;
}
