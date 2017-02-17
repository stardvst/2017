#include <iostream>
#include "AList.hpp"
#include "SLList.hpp"
#include "DLList.hpp"


int main() {

  // array based list
  AList<int> al(10);

  //al.move_to_start(); // assert

  std::cout << "array based list\n-----------------------\nis empty: "
    << std::boolalpha << al.empty() << ", size: " << al.get_size() << '\n';

  al.insert(5);  
  al.insert(-3);
  al.insert(4);
  al.insert(5);
  al.insert(-6);
  al.insert(1);

  std::cout << "\nlist: ";
  al.move_to_start();
  std::cout << al.get_value() << " ";
  while(al.next()) {
    std::cout << al.get_value() << " ";
  }

  std::cout << "\nmax: " << al.get_max();
  std::cout << "\nsize: " << al.get_size();
  al.remove_max_values();
  al.erase(1);
  al.erase_curr();

  std::cout << "\nremoved max values, 1 and current: ";
  al.move_to_start();
  std::cout << al.get_value() << " ";
  while(al.next()) {
    std::cout << al.get_value() << " ";
  }  
  //al.move_to(100); // assert






  // singly linked list
  SLList<int> sll;
  std::cout << "\n\n\nsingly linked list\n------------------------\nis empty: "
    << std::boolalpha << sll.empty() << ", size: " << sll.get_size() << '\n';

  sll.insert(5);
  sll.insert(-3);
  sll.insert(4);
  sll.insert(5);
  sll.insert(-6);
  sll.insert(1);

  std::cout << "\nlist: ";
  sll.move_to_start();
  while(sll.next()) {
    std::cout << sll.get_value() << " ";
  }

  std::cout << "\nmax: " << sll.get_max();
  std::cout << "\nsize: " << sll.get_size();
  sll.remove_max_values();
  sll.erase(1);
  sll.erase_curr();

  std::cout << "\nremoved max values, 1 and current: ";
  sll.move_to_start();
  while(sll.next()) {
    std::cout << sll.get_value() << " ";
  }



  
  // doubly linked list
  DLList<int> dll;
  std::cout << "\n\n\ndoubly linked list\n------------------------\nis empty: "
    << std::boolalpha << dll.empty() << ", size: " << dll.get_size() << '\n';

  dll.insert(5);
  dll.insert(-3);
  dll.insert(4);
  dll.insert(5);
  dll.insert(-6);
  dll.insert(1);

  std::cout << "\nlist: ";
  dll.move_to_start();
  while(dll.next()) {
    std::cout << dll.get_value() << " ";
  }

  std::cout << "\nmax: " << dll.get_max();
  std::cout << "\nsize: " << dll.get_size();
  dll.remove_max_values();
  dll.erase(1);
  dll.erase_curr();

  std::cout << "\nremoved max values, 1 and current: ";
  dll.move_to_start();
  while(dll.next()) {
    std::cout << dll.get_value() << " ";
  }

  std::cin.get();
}