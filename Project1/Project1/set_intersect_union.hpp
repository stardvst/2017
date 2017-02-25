#ifndef SET_INTERSECT_UNION
#define SET_INTERSECT_UNION

#include "Set.hpp"


template <typename T>
void get_intersection(List<T>* set1, List<T>* set2, List<T>* result) {
  size_t size1 = set1->get_size();
  size_t size2 = set2->get_size();
  size_t count1 = 0;
  size_t count2 = 0;

  set1->move_to_start();
  set2->move_to_start();

  while(count1 < size1 && count2 < size2) {
    if(set1->get_value() > set2->get_value()) {
      set1->next();
      ++count1;
    } else if(set1->get_value() < set2->get_value()) {
      set2->next();
      ++count2;
    } else {
      if(result->empty()) {
        result->insert(set1->get_value());
      } else if(!find(result, set1->get_value())) {
        result->insert(set1->get_value());
      }
      set1->next();
      set2->next();
      ++count1;
      ++count2;
    }
  }
}


template <typename T>
void get_union(List<T>* set1, List<T>* set2, List<T>* result) {
  size_t size1 = set1->get_size();
  size_t size2 = set2->get_size();
  size_t count1 = 0;
  size_t count2 = 0;

  set1->move_to_start();
  set2->move_to_start();

  for(T value; count1 < size1 && count2 < size2; ) {
    if(set1->get_value() > set2->get_value()) {
      value = set1->get_value();
      set1->next();
      ++count1;
    } else if(set1->get_value() < set2->get_value()) {
      value = set2->get_value();
      set2->next();
      ++count2;
    } else {
      value = set1->get_value();
      set1->next();
      set2->next();
      ++count1;
      ++count2;
    }

    if(result->empty()) {
      result->insert(value);
    } else if(!find(result, value)) {
      result->insert(value);
    }
  }

  while(count1++ < size1) {
    if(!find(result, set1->get_value())) {
      result->insert(set1->get_value());
    }
    set1->next();
  }

  while(count2++ < size2) {
    if(!find(result, set2->get_value())) {
      result->insert(set2->get_value());
    }
    set2->next();
  }
}


template <typename T>
bool find(List<T>* set, const T& value) {
  if(value == set->get_value()) {
    return true;
  }
  return false;
}


#endif // !set_INTERSECT_UNION
