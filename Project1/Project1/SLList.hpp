#ifndef SLLIST_HPP
#define SLLIST_HPP

#include <iostream>
#include <cassert>
#include <numeric>
#include "List.hpp"


template <typename T>
class SLList : public List<T> {
public:
  SLList() { init(); }
  ~SLList() { remove_all(); }

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

  T get_max() const { return max_value; }
  void remove_max_values();

private:
  void init();
  void remove_all();

private:
  struct Node {
    T data;
    Node* next;
    Node(T d = T(), Node* n = NULL) : data(d), next(n) {}
  };
private:
  Node* head;
  Node* current;
  Node* tail;
  size_t size;
  T max_value;
};


template <typename T>
void SLList<T>::init() {
  head = current = tail = new Node;
  size = 0;
  max_value = std::numeric_limits<T>::min();
}

template <typename T>
bool SLList<T>::insert(const T& x) {
  current->next = new Node(x, current->next);
  if(current == tail) {
    tail = current->next;
  }
  if(x > max_value) {
    max_value = x;
  }
  ++size;
  return true;
}

template <typename T>
bool SLList<T>::append(const T& x) {
  tail->next = new Node(x);
  tail = tail->next;
  if(x > max_value) {
    max_value = x;
  }
  ++size;
  return true;
}

template <typename T>
bool SLList<T>::erase(const T& x) {
  assert(size != 0 && "list is empty");

  move_to_start();
  for(; current != tail && current->next; current = current->next) {
    if(x == current->next->data) {
      Node* tmp = current->next;
      current->next = tmp->next;
      delete tmp;
      --size;
      return true;
    }
  }

  if(x == current->data) {
    delete tail;
    tail = current;
    tail->next = 0;
    return true;
  }
}

template <typename T>
bool SLList<T>::erase_curr() {
  assert(size != 0 && "list is empty");
  Node* tmp = current->next;
  current->next = tmp->next;
  if(tail == tmp) {
    tail = current;
  }
  delete tmp;
  --size;
  return true;
}

template <typename T>
bool SLList<T>::clear() {
  remove_all();
  init();
  return true;
}

template <typename T>
void SLList<T>::move_to_start() {
  assert(size != 0 && "list is empty");
  current = head;
}

template <typename T>
void SLList<T>::move_to(int pos) {
  assert(pos >= 0 && pos < size && "pos out of range");
  move_to_start();
  while(pos--) {
    next();
  }
}

template <typename T>
bool SLList<T>::next() {
  if(current->next) {
    current = current->next;
    return true;
  }
  return false;
}

template <typename T>
int SLList<T>::curr_pos() const {
  Node* tmp = current;
  int i = 0;
  while(tmp != current && ++i) {
    tmp = tmp->next;
  }
  return i;
}

template <typename T>
void SLList<T>::remove_max_values() {
  if(size != 0) {
    current = head->next;
    for(; current != 0; current = current->next) {
      if(max_value == current->data) {
        erase(max_value);
      }
    }
  }
}

template <typename T>
void SLList<T>::remove_all() {
  while(head != NULL) {
    current = head;
    head = head->next;
    delete current;
  }
}

#endif // !SLLIST_HPP
