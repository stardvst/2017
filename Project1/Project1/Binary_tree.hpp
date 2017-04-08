#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <stack>
#include <queue>
#include "Node.hpp"


template<typename T>
class Binary_tree {
public:
  Binary_tree(Node<T>* r = 0) : root(r) {}

  void inorder() const;
  void inorder_iter() const;

  void postorder() const;
  void preorder() const;
  void levelorder() const;

private:
  void _inorder(Node<T>*) const;
  void _postorder(Node<T>*) const;
  void _preorder(Node<T>*) const;
  void _levelorder(Node<T>*) const;
private:
  Node<T>* root;
};


template<typename T>
void Binary_tree<T>::inorder() const {
  _inorder(root);
}

template<typename T>
void Binary_tree<T>::inorder_iter() const {
  std::stack<Node<T>*> stack;
  Node<T>* node = root;

  while(node || !stack.empty()) {
    if(node) {
      stack.push(node);
      node = node->left;
    } else {
      node = stack.top();
      stack.pop();
      std::cout << node->value << ' ';
      node = node->right;
    }
  }
}

template<typename T>
void Binary_tree<T>::postorder() const {
  _postorder(root);
}

template<typename T>
void Binary_tree<T>::preorder() const {
  _preorder(root);
}

template<typename T>
void Binary_tree<T>::levelorder() const {
  if(root != 0) {
    std::queue<Node<T>*> queue;
    queue.push(root);

    while(!queue.empty()) {
      Node<T>* node = queue.front();
      queue.pop();

      std::cout << node->value << ' ';

      if(node->left) {
        queue.push(node->left);
      }
      if(node->right) {
        queue.push(node->right);
      }
    }
  }
}

template<typename T>
void Binary_tree<T>::_inorder(Node<T>* ptr) const {
  if(ptr != 0) {
    _inorder(ptr->left);
    std::cout << ptr->value << ' ';
    _inorder(ptr->right);
  }
}

template<typename T>
void Binary_tree<T>::_postorder(Node<T>* ptr) const {
  if(ptr != 0) {
    _postorder(ptr->left);
    _postorder(ptr->right);
    std::cout << ptr->value << ' ';
  }
}

template<typename T>
void Binary_tree<T>::_preorder(Node<T>* ptr) const {
  if(ptr != 0) {
    std::cout << ptr->value << ' ';
    _preorder(ptr->left);
    _preorder(ptr->right);
  }
}


#endif // !BINARY_TREE_HPP
