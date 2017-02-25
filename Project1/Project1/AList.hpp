#ifndef ALIST_HPP
#define ALIST_HPP

#include <cassert>
#include "List.hpp"


template <typename T>
class AList : public List<T> {
public:
  AList(size_t n) : list(new T[n]), size(0), max_size(n), current(0) {}
  ~AList() { delete[] list; }

  bool insert(const T&);
  bool append(const T&);

  bool erase(const T&);
  bool erase_curr();
  bool clear();

  void move_to_start();
  void move_to(int);
  bool next();

  T get_value() const;
  int curr_pos() const { return current; }
  bool empty() const { return size == 0; }
  size_t get_size() const { return size; }

  bool end() const { return current == size; }
private:
  T* list;
  size_t size;
  size_t max_size;
  int current;

  AList(const AList&) {}
  const AList& operator=(const AList&) {}
};


template <typename T>
bool AList<T>::insert(const T& x) {
  if(size < max_size) {
    for(size_t i = size; i > current; --i) {
      list[i] = list[i - 1];
    }
    list[current] = x;
    ++size;
    return true;
  }
  return false;
}

template <typename T>
bool AList<T>::append(const T& x) {
  if(size < max_size) {
    list[size++] = x;
    return true;
  }
  return false;
}

template <typename T>
bool AList<T>::erase(const T& x) {
  assert(size != 0);
  for(size_t i = 0; i < size; ++i) {
    if(list[i] == x) {
      for(size_t j = i; j < size - 1; ++j) {
        list[j] = list[j + 1];
      }
      --size;
      return true;
    }
  }
  return false;
}

template <typename T>
bool AList<T>::erase_curr() {
  assert(size != 0);
  for(size_t i = current; i < size - 1; ++i) {
    list[i] = list[i + 1];
  }
  --size;
  return true;
}

template <typename T>
bool AList<T>::clear() {
  assert(size != 0);
  delete[] list;
  list = new T[max_size];
  size = 0;
  current = 0;
  return true;
}

template <typename T>
void AList<T>::move_to_start() {
  assert(size != 0);
  current = 0;
}

template <typename T>
void AList<T>::move_to(int pos) {
  assert(pos >= 0 && pos < size);
  current = pos;
}

template <typename T>
bool AList<T>::next() {
  if(current + 1 < size) {
    ++current;
    return true;
  }
  return false;
}

template <typename T>
T AList<T>::get_value() const {
  assert(current >= 0 && current < size);
  return list[current];
}


#endif // !ALIST_HPP
