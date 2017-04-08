#include <exception>
#include <iostream>
#include "Binary_tree.hpp"
#include "Node.hpp"


int main() {
  
  Node<char>* c = new Node<char>('c');
  Node<char>* e = new Node<char>('e');

  Node<char>* b = new Node<char>('b', c);
  Node<char>* d = new Node<char>('d', 0, e);
  Node<char>* a = new Node<char>('a', b, d);


  Binary_tree<int> tree(a);


  std::cout << "\ninorder: ";
  tree.inorder();

  std::cout << "\npostorder: ";
  tree.postorder();

  std::cout << "\npreorder: ";
  tree.preorder();

  std::cout << "\nlevelorder: ";
  tree.levelorder();

  std::cin.get();
  return 0;
}
