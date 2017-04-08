#include <exception>
#include <iostream>
#include "Virtual_memory.hpp"
#include "V_addr.hpp"
#include <iomanip>
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

  //Virtual_memory vm;

  //V_addr add1 = vm.allocate(20);
  //V_addr add2 = vm.allocate(12);
  //V_addr add3 = vm.allocate(4);

  //try {
  //  vm.free(add2);
  //} catch(const std::exception& e) {
  //  std::cerr << e.what();
  //}

  //try {
  //  vm[add1] = 4;
  //  std::cout << static_cast<int>(static_cast<const Virtual_memory>(vm)[add1]) << '\n'; // call const operator[]
  //} catch(const std::exception& e) {
  //  std::cerr << e.what();
  //}

  //try {
  //  vm.free(add3);
  //} catch(const std::exception& e) {
  //  std::cerr << e.what();
  //}

  //try {
  //  vm[add3] = 5;
  //} catch(const std::exception& e) {
  //  std::cerr << e.what();
  //}


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
