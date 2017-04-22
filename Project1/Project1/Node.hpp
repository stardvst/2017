#ifndef NODE_HPP
#define NODE_HPP


template<typename T>
struct Node {
  T value;
  Node* left;
  Node* right;
  Node(T v, Node* l = 0, Node* r = 0) : value(v), left(l), right(r) {}
};

#endif // !NODE_HPP
