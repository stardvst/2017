#ifndef NODE_HPP
#define NODE_HPP

#include <cstddef>

template<typename T>
class Node {
public:
  T data;
  Node* prev;
  Node* next;

  Node(T d = T(), Node* p = 0, Node* n = 0) : data(d), prev(p), next(n) {
    if(prev) {
      prev->next = this;
    }
    if(next) {
      next->prev = this;
    }
  }

  void* operator new(size_t) {
    if(freelist == 0) {
      return ::new Node;
    }
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
Node<T>* Node<T>::freelist = 0;


#endif // !NODE_HPP
