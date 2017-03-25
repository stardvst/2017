#ifndef DLLIST_HPP
#define DLLIST_HPP

#include <iostream>
#include <cassert>
#include <numeric>
#include "List.hpp"
#include "Node_freelist.hpp"


template <typename T>
class DLList : public List<T> {
public:
  DLList() { init(); }
  ~DLList() { remove_all(); }

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

  bool end() const { return current == tail->next; }
private:
  void init();
  void remove_all();
private:
  Node<T>* head;
  Node<T>* current;
  Node<T>* tail;
  size_t size;
  
  DLList(const DLList&) {}
  const DLList& operator=(const DLList&) {}
};


template <typename T>
void DLList<T>::init() {
  head = current = tail = new Node<T>;
  size = 0;
}

template <typename T>
bool DLList<T>::insert(const T& x) {
  new Node<T>(x, current, current->next);
  if(current == tail) {
    tail = current->next;
  }
  current = current->next;
  ++size;
  return true;
}

template <typename T>
bool DLList<T>::append(const T& x) {
  tail->next = new Node<T>(x, tail, NULL);
  tail = tail->next;
  ++size;
  return true;
}

template <typename T>
bool DLList<T>::erase(const T& x) {
  assert(size != 0 && "list is empty");

  move_to_start();

  for(Node<T>* prev = head; current; prev = current, current = current->next) {
    if(x == current->data) {
      prev->next = current->next;
      if(tail == current) {
        tail = prev;
      } else {
        current->next->prev = prev; // else there is an element
      }
      delete current;
      --size;
      move_to_start();
      return true;
    }
  }

  return false;
}

template <typename T> // ???
bool DLList<T>::erase_curr() {
  assert(size != 0 && "list is empty");
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
bool DLList<T>::clear() {
  remove_all();
  init();
  return true;
}

template <typename T>
void DLList<T>::move_to_start() {
  assert(size != 0);
  current = head->next;
}

template <typename T>
void DLList<T>::move_to(int pos) {
  assert(pos >= 0 && pos < size);
  move_to_start();
  while(pos--) {
    next();
  }
}

template <typename T>
bool DLList<T>::next() {
  if(current != tail) {
    current = current->next;
    return true;
  }
  return false;
}

template <typename T>
int DLList<T>::curr_pos() const {
  Node<T>* tmp = head;
  int i = 0;
  while(tmp != current) {
    ++i;
    tmp = tmp->next;
  }
  return i;
}

template <typename T>
void DLList<T>::remove_all() {
  while(head != NULL) {
    current = head;
    head = head->next;
    delete current;
  }
}

#endif // !DLList_HPP
