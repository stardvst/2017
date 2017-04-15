#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <algorithm>
#include <iostream>
#include <numeric>
#include <stack>
#include <queue>
#include "Element.hpp"
#include "Node.hpp"


template<typename T>
class Binary_tree {
public:
  Binary_tree(Element<T>*, int);
  ~Binary_tree() {
    //_destroy(root);
    _destroy_iter();
    root = 0;
  }

  void levelorder() const;
  int leaf_count() const;
  int height() const;
  int width() const;
private:
  int _leaf_count(Node<T>*) const;
  int _height(Node<T>*) const;
  int _width(Node<T>*) const;
  void _destroy(Node<T>*);
  void _destroy_iter();
private:
  Node<T>* root;
};


template<typename T>
Binary_tree<T>::Binary_tree(Element<T>* arr, int size) {
  Node<T>** new_arr = new Node<T>*[size];

  for(int i = 0; i < size; ++i) {
    new_arr[i] = new Node<T>(arr[i].value);
  }
  root = new_arr[0];

  for(int i = 0; i < size; ++i) {
    if(arr[i].left != -1) {
      new_arr[i]->left = new_arr[arr[i].left];
    }
    if(arr[i].right != -1) {
      new_arr[i]->right = new_arr[arr[i].right];
    }
  }
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
int Binary_tree<T>::leaf_count() const {
  return _leaf_count(root);
}

template<typename T>
int Binary_tree<T>::_leaf_count(Node<T>* ptr) const {
  if(ptr == 0) {
    return 0;
  }
  if(ptr->left == 0 && ptr->right == 0) {
    return 1;
  }
  return _leaf_count(ptr->left) + _leaf_count(ptr->right);
}

template<typename T>
int Binary_tree<T>::height() const {
  return _height(root);
}

template<typename T>
int Binary_tree<T>::_height(Node<T>* ptr) const {
  if(ptr == 0 || (ptr->left == 0 && ptr->right == 0)) {
    return 0;
  }
  return 1 + std::max(_height(ptr->left), _height(ptr->right));
}

template<typename T>
int Binary_tree<T>::width() const {
  return _width(root);
}

template<typename T>
int Binary_tree<T>::_width(Node<T>* ptr) const {
  if(!root) {
    return 0;
  }

  std::queue<Node<T>*> queue;
  int level_count = 1;
  int max = std::numeric_limits<int>::min();

  queue.push(ptr);
  while(!queue.empty()) {
    level_count = static_cast<int>(queue.size());
    if(level_count > max) {
      max = level_count;
    }

    while(level_count > 0) {
      Node<T>* node = queue.front();
      queue.pop();
      if(node->left) {
        queue.push(node->left);
      }
      if(node->right) {
        queue.push(node->right);
      }
      --level_count;
    }

  }

  return max;
}

template<typename T>
void Binary_tree<T>::_destroy(Node<T>* ptr) {
  if(ptr != 0) {
    _destroy(ptr->left);
    _destroy(ptr->right);
    delete ptr;
  }
}

template<typename T>
void Binary_tree<T>::_destroy_iter() {
  if(root == 0) {
    return;
  }

  std::queue<Node<T>*> queue;
  queue.push(root);

  while(!queue.empty()) {
    Node<T>* node = queue.front();
    queue.pop();

    if(node->left) {
      queue.push(node->left);
    }
    if(node->right) {
      queue.push(node->right);
    }

    delete node;
  }
}


#endif // !BINARY_TREE_HPP
