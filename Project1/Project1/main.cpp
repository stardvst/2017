#include <iostream>
#include <algorithm>
#include <functional>
#include <list>

std::list<int> get_intersection(const std::list<int>& l1, const std::list<int>& l2) {
  std::list<int> result;

  for(std::list<int>::const_iterator l1it = l1.begin(); l1it != l1.end(); ++l1it) {
    std::list<int>::const_iterator l2it = l2.begin();
    while(l2it != l2.end() && *l2it != *l1it) {
      ++l2it;
    }
    if(l2it != l2.end()) {
      if(*l1it == *l2it && std::find(result.begin(), result.end(), *l1it) == result.end()) {
        result.push_back(*l1it);
      }
    }
  }

  return result;
}

template<typename C>
std::list<int> get_union(const std::list<int>& l1, const std::list<int>& l2, C cmp) {
  std::list<int> result;

  std::list<int>::const_iterator l1it = l1.begin();
  std::list<int>::const_iterator l2it = l2.begin();

  while(l1it != l1.end() && l2it != l2.end()) {
    if(cmp(*l1it, *l2it)) {
      result.push_back(*l1it);
      ++l1it;
    } else if(cmp(*l2it, *l1it)) {
      result.push_back(*l2it);
      ++l2it;
    } else {
      result.push_back(*l1it);
      ++l1it;
      ++l2it;
    }
  }

  while(l1it != l1.end()) {
    if(std::find(result.begin(), result.end(), *l1it) == result.end()) { result.push_back(*l1it); }
    ++l1it;
  }
  while(l2it != l2.end()) {
    if(std::find(result.begin(), result.end(), *l2it) == result.end()) { result.push_back(*l2it); }
    ++l2it;
  }

  return result;
}


int main() {

  std::list<int> l1;
  std::list<int> l2;

  l1.push_back(4);
  l1.push_back(5);
  l1.push_back(2);
  l1.push_back(-5);
  l1.push_back(3);
  l1.push_back(-1);
  l1.push_back(0);
  l1.push_back(7);

  l2.push_back(5);
  l2.push_back(0);
  l2.push_back(8);
  l2.push_back(6);
  l2.push_back(7);
  l2.push_back(3);
  l2.push_back(-10);

  l1.sort(std::greater<int>());
  std::cout << "L1\t";
  for(std::list<int>::const_iterator it = l1.begin(); it != l1.end(); ++it) {
    std::cout << *it << " -> ";
  }
  std::cout << "NULL\n\n";

  l2.sort(std::greater<int>());
  std::cout << "L2\t";
  for(std::list<int>::const_iterator it = l2.begin(); it != l2.end(); ++it) {
    std::cout << *it << " -> ";
  }
  std::cout << "NULL\n\n";

  std::list<int> result = get_intersection(l1, l2);
  std::cout << "L1&L2\t";
  for(std::list<int>::const_iterator it = result.begin(); it != result.end(); ++it) {
    std::cout << *it << " -> ";
  }
  std::cout << "NULL\n\n";

  result = get_union(l1, l2, std::greater<int>());
  std::cout << "L1|L2\t";
  for(std::list<int>::const_iterator it = result.begin(); it != result.end(); ++it) {
    std::cout << *it << " -> ";
  }
  std::cout << "NULL";

  std::cin.get();
  return 0;
}