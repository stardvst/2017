#include <iostream>
#include "Set.hpp"
#include "set_intersect_union.hpp"


template <typename T>
void print_list(List<T>* list) {
  if(list->get_size() != 0) {
    int count = 0;
    list->move_to_start();
    while(count++ < list->get_size()) {
      std::cout << list->get_value() << " -> ";
      list->next();
    }
    std::cout << "NULL";
  } else {
    std::cout << "empty";
  }
}


int main() {

  std::cout << "intersection and union\n-------------------------\n";
  List<int>* set1 = new Set<int>;
  List<int>* set2 = new Set<int>;
  List<int>* result = new Set<int>;

  int number = 0;
  while(number <= 0) {
    std::cout << "\nenter the number of elements in set 1: ";
    std::cin >> number;
  }

  int current;
  for(int i = 0; i < number; ++i) {
    std::cout << "set1[" << i << "] = ";
    std::cin >> current;
    set1->insert(current);
  }

  std::cout << "\nset1: ";
  print_list(set1);

  for(number = 0; number <= 0; ) {
    std::cout << "\n\nenter the number of elements in set 2: ";
    std::cin >> number;
  }
  for(int i = 0; i < number; ++i) {
    std::cout << "set2[" << i << "] = ";
    std::cin >> current;
    set2->insert(current);
  }

  std::cout << "\nset2: ";
  print_list(set2);

  get_intersection(set1, set2, result);
  std::cout << "\n\nset1 & set2 intersection: ";
  print_list(result);

  result->clear();
  
  get_union(set1, set2, result);
  std::cout << "\n\nset1 and set2 union: ";
  print_list(result);

  std::cin.get();
  std::cin.get();
}
