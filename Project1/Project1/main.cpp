#include <exception>
#include <iostream>
#include "Binary_tree.hpp"
#include "Node.hpp"


template<typename T>
Node<T>* array_to_tree(const std::vector<T>& nodes, int index) {
  if(index < nodes.size()) {
    T value = nodes[index];
    if(value != -1) {
      Node<T>* root = new Node<T>(value);
      root->left = array_to_tree(nodes, 2 * index + 1);
      root->right = array_to_tree(nodes, 2 * index + 2);
      return root;
    }
  }
  return 0;
}

int main() {

  std::vector<int> nodes;
  int number = 0;
  while(number <= 0) {
    std::cout << "Enter the number of nodes: ";
    std::cin >> number;
  }

  for(int i = 0; i < number; ++i) {
    int current;
    std::cout << "nodes[" << i << "] = ";
    std::cin >> current;
    nodes.push_back(current);
  }


  Binary_tree<int> tree(array_to_tree(nodes, 0));

  std::cout << "\ninorder:      ";
  tree.inorder();

  std::cout << "\ninorder iter: ";
  tree.inorder_iter();

  std::cout << "\npostorder:    ";
  tree.postorder();
  
  std::cout << "\npreorder:     ";
  tree.preorder();

  std::cout << "\nlevelorder:   ";
  tree.levelorder();

  std::cin.get();
  std::cin.get();
  return 0;
}
