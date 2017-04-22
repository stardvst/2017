#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
#include "Visitor.hpp"
#include "Node.hpp"


template<typename T>
class Binary_search_tree {
public:
  Binary_search_tree(Node<T>* r = 0) : root(r) {}
  ~Binary_search_tree() {
    //_destroy(root);
    _destroy_iter();
    root = 0;
  }

  void insert_iter(const T&);
  void insert(const T&);
  Node<T>* find(const T&) const;
  bool is_full() const;

  template<typename V>
  void levelorder(const V&) const;

  int leaf_count() const;
  int height() const;
  int width() const;
private:
  int _leaf_count(const Node<T>*) const;
  int _height(const Node<T>*) const;
  int _width(Node<T>*) const;
  void _destroy(Node<T>*);
  void _destroy_iter();

  void _insert(Node<T>*, const T&);
private:
  Node<T>* root;
};


template<typename T>
void Binary_search_tree<T>::insert(const T& value) {
  _insert(root, value);
}

template<typename T>
void Binary_search_tree<T>::_insert(Node<T>* node, const T& value) {
  if(!root) {
    root = new Node<T>(value);
    return;
  }
  if(value <= node->value) {
    if(node->left) {
      _insert(node->left, value);
    } else {
      node->left = new Node<T>(value);
    }
  } else if(node->right) {
    _insert(node->right, value);
  } else {
    node->right = new Node<T>(value);
  }
}

template<typename T>
void Binary_search_tree<T>::insert_iter(const T& value) {
  Node<T>* current = root;
  Node<T>* tmp = 0;

  while(current != 0) {
    tmp = current;
    if(value <= current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  Node<T>* node = new Node<T>(value);
  if(tmp == 0) {
    root = node;
  } else if(value <= tmp->value) {
    tmp->left = node;
  } else {
    tmp->right = node;
  }
}

template<typename T>
Node<T>* Binary_search_tree<T>::find(const T& value) const {
  Node<T>* node = root;
  while(node && node->value != value) {
    if(value < node->value) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

template<typename T>
bool Binary_search_tree<T>::is_full() const {
  if(!root) {
    return false;
  }

  std::queue<Node<T>*> queue;
  Node<T>* node = root;
  queue.push(node);

  while(!queue.empty()) {
    node = queue.front();
    queue.pop();

    if((node->left == 0 && node->right) ||
      (node->left && node->right == 0)) {
      return false;
    }

    if(node->left && node->right) {
      queue.push(node->left);
      queue.push(node->right);
    }
  }

  return true;
}

template<typename T>
template<typename V>
void Binary_search_tree<T>::levelorder(const V& visitor) const {
  if(!root) {
    return;
  }

  std::queue<Node<T>*> queue;
  queue.push(root);

  while(!queue.empty()) {
    Node<T>* node = queue.front();
    queue.pop();

    visitor(node->value);

    if(node->left) {
      queue.push(node->left);
    }
    if(node->right) {
      queue.push(node->right);
    }
  }
}


template<typename T>
int Binary_search_tree<T>::leaf_count() const {
  return _leaf_count(root);
}

template<typename T>
int Binary_search_tree<T>::_leaf_count(const Node<T>* ptr) const {
  if(!ptr) {
    return 0;
  }
  if(ptr->left == 0 && ptr->right == 0) {
    return 1;
  }
  return _leaf_count(ptr->left) + _leaf_count(ptr->right);
}

template<typename T>
int Binary_search_tree<T>::height() const {
  return _height(root);
}

template<typename T>
int Binary_search_tree<T>::_height(const Node<T>* ptr) const {
  if(!ptr) {
    return 0;
  }
  if(ptr->left == 0 && ptr->right == 0) {
    return 1;
  }
  return 1 + std::max(_height(ptr->left), _height(ptr->right));
}

template<typename T>
int Binary_search_tree<T>::width() const {
  return _width(root);
}

template<typename T>
int Binary_search_tree<T>::_width(Node<T>* ptr) const {
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
void Binary_search_tree<T>::_destroy(Node<T>* ptr) {
  if(ptr != 0) {
    _destroy(ptr->left);
    _destroy(ptr->right);
    delete ptr;
  }
}

template<typename T>
void Binary_search_tree<T>::_destroy_iter() {
  if(!root) {
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


#endif // !BINARY_SEARCH_TREE_HPP
