#include <iostream>
#include "Binary_search_tree.hpp"
#include "Visitor.hpp"
#include "Node.hpp"


int main() {

  int size = 0;
  while(size <= 0) {
    std::cout << "Enter the number of nodes: ";
    std::cin >> size;
  }

  Binary_search_tree<int> tree;

  for(int i = 0; i < size; ++i) {
    std::cout << "Enter node value: ";
    int value;
    std::cin >> value;
    tree.insert_iter(value); // or insert(value);
  }


  std::cout << "\nlevelorder: ";
  tree.levelorder(Print<int>());

  Max<int> m;
  tree.levelorder(m);
  std::cout << "\nmax: " << m.max;

  Sum<int> s;
  tree.levelorder(s);
  std::cout << "\nsum of elements: " << s.sum;
  

  std::cout << "\n\n# of leaves: " << tree.leaf_count()
    << "\ntree height: " << tree.height()
    << "\ntree width: " << tree.width()
    << "\nis full: " << std::boolalpha << tree.is_full();


  char c;
  std::cout << "\n\nfind a value? (y or n): ";
  std::cin >> c;
  while(c != 'n') {
    int value;
    std::cout << "value: ";
    std::cin >> value;
    
    std::cout << value << (tree.find(value) ? " found" : " not found") << '\n';
    
    std::cout << "\nfind a value? (y or n): ";
    std::cin >> c;
  }


  std::cin.get();
  return 0;
}
