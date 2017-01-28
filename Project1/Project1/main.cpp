#include <iostream>

struct Node {
  Node* prev;
  int data;
  Node* next;
  Node(Node* p, int d, Node* n) :prev(p), data(d), next(n) {}
};

class iterator {
  friend class List;
public:
  iterator(Node* ptr) :node(ptr) {}
  int operator*() const { return node->data; }
  iterator& operator++() { node = node->next; return *this; }
  bool operator==(const iterator& ob) const { return ob.node == node; }
  bool operator!=(const iterator& ob) const { return ob.node != node; }
private:
  Node* node;
};

class List {
public:
  List() : first(0), last(0) {}

  void insert(iterator it, int value) {
    if(first == last) {
      Node* newNode = new Node(0, value, 0);

      if(!first) {
        first = last = newNode;
      } else {
        first = newNode;
        newNode->next = last;
      }
    } else {
      _insert(it.node, value);
    }
  }

  iterator begin() { return iterator(first); }
  iterator end() { return iterator(0); }
private:
  Node* first;
  Node* last;

  void _insert(Node* node, int value) {
    Node* newNode = new Node(0, value, 0);
    if(node == first) {
      first = newNode;
    }
    newNode->next = node;
    if(node->prev) {
      node->prev->next = newNode;
    }
    newNode->prev = node->prev;
    node->prev = newNode;
    //node->next->prev = newNode;
    
    
    //node->next = newNode;
  }
};


template<typename Iterator, typename T>
iterator find(Iterator start, Iterator end, const T& x) {
  while(start != end) {
    if(*start == x) {
      return start;
    }
    ++start;
  }
  return end;
}


int main() {

  List l;
  l.insert(l.begin(), 6);
  l.insert(l.begin(), 7);
  l.insert(l.begin(), 8);
  l.insert(l.begin(), 1);
  l.insert(l.begin(), 7);
  l.insert(l.begin(), 3);

  for(iterator it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << " -> ";
  }
  std::cout << "NULL\n\n";

  iterator occ = find(l.begin(), ++++++++l.begin(), 7);
  while(occ != l.end()) {
    std::cout << *occ << " -> ";
    ++occ;
  }
  std::cout << "NULL";

  std::cin.get();
  return 0;
}