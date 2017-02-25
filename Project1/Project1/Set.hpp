#ifndef SET_HPP
#define SET_HPP

#include <cassert>
#include "List.hpp"
#include "Node_freelist.hpp"


template<typename T>
class Set : public List<T> {
public:
  Set() { init(); }
  ~Set() { remove_all(); }

  bool insert(const T&);
  bool append(const T&);

  bool erase(const T&);
  bool erase_curr();
  bool clear();

  void move_to_start();
  void move_to(int);
  bool next();

  int curr_pos() const;
  T get_value() const { return current->data; }
  bool empty() const { return size == 0; }
  size_t get_size() const { return size; }
private:
  void remove_all();
  void init();
private:
  Node<T>* head;
  Node<T>* current;
  Node<T>* tail;
  size_t size;

  Set(const Set&) {}
  Set& operator=(const Set&) {}
};


template <typename T>
void Set<T>::init() {
  head = current = tail = new Node<T>;
  size = 0;
}

template <typename T> // insert and sort desc
bool Set<T>::insert(const T& x) {
  Node<T>* newNode = new Node<T>(x, NULL, NULL);
  current = head->next;

  if(head == tail) {
    head->next = newNode;
    newNode->prev = head;
    tail = newNode;
  } else if(x > current->data) { // insert before head
    newNode->next = current;
    current->prev = newNode;
    head->next = newNode;
    newNode->prev = head;
  } else {
    Node<T>* tmp = NULL;

    while(current && x <= current->data) {
      tmp = current;
      current = current->next;
    }

    if(!current) { // insert as last node
      tmp->next = newNode;
      newNode->prev = tmp;
      tail = newNode;
    } else { // insert in the middle
      tmp->next = newNode;
      newNode->prev = tmp;
      current->prev = newNode;
      newNode->next = current;
    }
  }
  current = head->next;
  ++size;
  return true;
}

template <typename T>
bool Set<T>::append(const T& x) {
  insert(x);
  return true;
}

template <typename T>
bool Set<T>::erase(const T& x) {
  assert(size != 0);

  for(current = head; current != tail && current->next; current = current->next) {
    if(x == current->next->data) {
      Node<T>* tmp = current->next;
      current->next = tmp->next;
      if(tmp->next) {
        tmp->next->prev = tmp->prev;
      }
      if(tmp == tail) {
        tail = tmp->prev;
      }
      delete tmp;
      --size;
      return true;
    }
  }

  if(x == current->data) {
    delete tail;
    tail = current;
    tail->next;
    return true;
  }
  return false;
}

template <typename T>
bool Set<T>::erase_curr() {
  assert(size != 0);
  Node<T>* tmp = current->next;
  current->next = tmp->next;
  tmp->next->prev = tmp->prev;
  if(tail == tmp) {
    tail = current;
  }
  delete tmp;
  --size;
  return true;
}

template <typename T>
bool Set<T>::clear() {
  remove_all();
  init();
  return true;
}

template <typename T>
void Set<T>::move_to_start() {
  assert(size != 0);
  current = head->next;
}

template <typename T>
void Set<T>::move_to(int pos) {
  assert(pos >= 0 && pos < size);
  move_to_start();
  while(pos--) {
    next();
  }
}

template <typename T>
bool Set<T>::next() {
  if(current != tail) {
    current = current->next;
    return true;
  }
  return false;
}

template <typename T>
int Set<T>::curr_pos() const {
  Node<T>* tmp = current;
  int i = 0;
  while(tmp != current && ++i) {
    tmp = tmp->next;
  }
  return i;
}

template <typename T>
void Set<T>::remove_all() {
  Node<T>* tmp;
  while(head) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}


#endif // !SET_HPP
