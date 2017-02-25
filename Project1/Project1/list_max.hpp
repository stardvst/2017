#ifndef MAX_HPP
#define MAX_HPP

#include <iostream>
#include <limits>
#include "List.hpp"


template <typename T>
T get_max(List<T>* list) {

  T max = std::numeric_limits<T>::min();

  if(list->get_size() == 0) {
    return max;
  }

  list->move_to_start();
  size_t size = 0;
  while(size++ < list->get_size()) {
    if(list->get_value() > max) {
      max = list->get_value();
    }
    list->next();
  }
  return max;
}


template <typename T>
void remove_max_values(List<T>* list) {
  if(list->empty()) {
    throw std::exception("list is empty, no max values to remove");
  }

  T max = get_max(list);
  list->move_to_start();

  size_t size = list->get_size();
  AList<T>* alp = dynamic_cast<AList<T>*>(list);

  for(int count = 0; count < size; ) {
    if(list->get_value() == max) {
      list->erase(max);
      --size;
      if(alp == 0) { list->next(); } // don't advance array current because it uses an index
    } else {
      ++count;
      list->next();
    }
  }
}


#endif // !MAX_HPP
