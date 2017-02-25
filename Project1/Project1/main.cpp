#include <iostream>
#include "AList.hpp"
#include "SLList.hpp"
#include "DLList.hpp"
#include "list_max.hpp"


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

  // array based list
  List<int>* list = new AList<int>(10);

  //list->move_to_start(); // assert

  std::cout << "array based list\n-----------------------\n"
    "is empty: " << std::boolalpha << list->empty() << 
    ", size: " << list->get_size() << '\n';

  int number = 0;
  while(number <= 0 || number > 10) {
    std::cout << "\nenter the number of elements (1-10): ";
    std::cin >> number;
  }
  int current;
  for(int i = 0; i < number; ++i) {
    std::cout << "list[" << i << "] = ";
    std::cin >> current;
    list->insert(current);
  }

  std::cout << "\nlist: "; 
  print_list(list);

  std::cout << "\nsize: " << list->get_size();
  std::cout << "\nmax: " << get_max(list);
  std::cout << "\n\nenter a value to erase: ";
  std::cin >> number;

  if(list->erase(number)) {
    std::cout << number << " deleted";
    std::cout << "\nlist: ";
    print_list(list);
  } else {
    std::cout << number << " not in the list";
  }

  std::cout << "\n\nremoving max values...";
  try {
    remove_max_values(list);
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\nlist: ";
  print_list(list);

  //list->move_to(100); // assert

  delete list;




  // singly linked list
  list = new SLList<int>;
  std::cout << "\n\n\n\nsingly linked list\n-----------------------\n"
    "is empty: " << std::boolalpha << list->empty() <<
    ", size: " << list->get_size() << '\n';

  for(number = 0; number <= 0; ) {
    std::cout << "\nenter the number of elements: ";
    std::cin >> number;
  }
  for(int i = 0; i < number; ++i) {
    std::cout << "list[" << i << "] = ";
    std::cin >> current;
    list->insert(current);
  }

  std::cout << "\nlist: ";
  print_list(list);

  std::cout << "\nsize: " << list->get_size();
  std::cout << "\nmax: " << get_max(list);
  std::cout << "\n\nenter a value to erase: ";
  std::cin >> number;

  if(list->erase(number)) {
    std::cout << number << " deleted";
    std::cout << "\nlist: ";
    print_list(list);
  } else {
    std::cout << number << " not in the list";
  }

  std::cout << "\n\nremoving max values...";
  try {
    remove_max_values(list);
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\nlist: ";
  print_list(list);

  delete list;




  // doubly linked list
  list = new DLList<int>;
  std::cout << "\n\n\n\ndoubly linked list\n-----------------------\n"
    "is empty: " << std::boolalpha << list->empty() <<
    ", size: " << list->get_size() << '\n';

  for(number = 0; number <= 0; ) {
    std::cout << "\nenter the number of elements: ";
    std::cin >> number;
  }
  for(int i = 0; i < number; ++i) {
    std::cout << "list[" << i << "] = ";
    std::cin >> current;
    list->insert(current);
  }

  std::cout << "\nlist: ";
  print_list(list);

  std::cout << "\nsize: " << list->get_size();
  std::cout << "\nmax: " << get_max(list);
  std::cout << "\n\nenter a value to erase: ";
  std::cin >> number;

  if(list->erase(number)) {
    std::cout << number << " deleted";
    std::cout << "\nlist: ";
    print_list(list);
  } else {
    std::cout << number << " not in the list";
  }

  std::cout << "\n\nremoving max values...";
  try {
    remove_max_values(list);
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\nlist: ";
  print_list(list);

  delete list;


  std::cin.get();
  std::cin.get();
}
