#ifndef NODE_HPP
#define NODE_HPP

#include <cstddef>

template <typename T>
class Node {
public:
  T data;
  Node* prev;
  Node* next;

  Node(T d, Node* p, Node* n) : data(d), prev(p), next(n) {
    if(prev) prev->next = this;
    if(next) next->prev = this;
  }
  Node(Node* p = NULL, Node* n = NULL) : prev(p), next(n) {
    if(prev) prev->next = this;
    if(next) next->prev = this;
  }

  void* operator new(size_t) {
    if(freelist == NULL) return ::new Node;
    Node* tmp = freelist;
    freelist = freelist->next;
    return tmp;
  }
  void operator delete(void* ptr) {
    static_cast<Node*>(ptr)->next = freelist;
    freelist = static_cast<Node*>(ptr);
  }
private:
  static Node<T>* freelist;
};


template <typename T>
Node<T>* Node<T>::freelist = NULL;


#endif // !NODE_HPP
