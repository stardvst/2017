#ifndef ALIST_HPP
#define ALIST_HPP

#include <cassert>
#include <limits>
#include "List.hpp"


template<typename T>
class AList : public List<T> {
public:
  AList(size_t n) : list(new T[n]), size(0),
    max_size(n), current(0), max_value(std::numeric_limits<T>::min()) {}
  ~AList() { delete[] list; }

  bool insert(const T&);
  bool append(const T&);

  bool erase(const T&);
  bool erase_curr();
  bool clear();

  void move_to_start();
  void move_to(int);
  bool next();

  T get_value() const { return list[current]; }
  int curr_pos() const { return current - 2; }
  bool empty() const { return size == 0; }
  size_t get_size() const { return size; }

  T get_max() const { return max_value; }
  void remove_max_values();

private:
  T* list;
  size_t size;
  size_t max_size;
  int current;
  T max_value;

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
    if(x > max_value) {
      max_value = x;
    }
    return true;
  }
  return false;
}

template <typename T>
bool AList<T>::append(const T& x) {
  if(size < max_size) {
    list[++size] = x;
    if(x > max_value) {
      max_value = x;
    }
    return true;
  }
  return false;
}

template <typename T>
bool AList<T>::erase(const T& x) {
  if(size == 0) return false;
  for(size_t i = 0; i < size; ++i) {
    if(list[i] == x) {
      for(size_t j = i; j < size; ++j) {
        list[j] = list[j + 1];
      }
      --size;
      return true;
    }
  }
}

template <typename T>
bool AList<T>::erase_curr() {
  if(size == 0) return false;
  for(size_t i = current; i < size; ++i) {
    list[i] = list[i + 1];
  }
  --size;
  return true;
}

template <typename T>
bool AList<T>::clear() {
  if(size != 0) {
    delete[] list;
    current = 0;
    list = new T[max_size];
    return true;
  }
  return false;
}

template <typename T>
void AList<T>::move_to_start() {
  assert(size != 0 && "list is empty");
  current = 0;
}

template <typename T>
void AList<T>::move_to(int pos) {
  assert(pos >= 0 && pos < size && "pos out of range");
  current = pos;
}

template <typename T>
bool AList<T>::next() {
  if(current < size - 1) {
    ++current;
    return true;
  }
  return false;
}

template <typename T>
void AList<T>::remove_max_values() {
  if(size != 0) {
    current = 0; // move_to_start();
    for(size_t i = 0; i < size; ) {
      if(list[i] == max_value) {
        for(size_t j = i; j < size; ++j) {
          list[j] = list[j + 1];
        }
        --size;
      } else {
        ++i;
        ++current; // next();
      }
    }
  }
  current = 0;
}


#endif // !ALIST_HPP
