#include <iostream>
#include <list>

//void printLots(const std::list<int>& l, const std::list<int>& p) {
//  for(std::list<int>::const_iterator pit = p.begin(); pit != p.end(); ++pit) {
//    if(*pit < 0 || *pit > l.size()) { continue; }
//    std::list<int>::const_iterator lit = l.begin();
//    std::advance(lit, *pit - 1);
//    std::cout << *lit << ' ';
//  }
//}

void printLots(const std::list<int>& l, const std::list<int>& p) {
  for(std::list<int>::const_iterator pit = p.begin(); pit != p.end(); ++pit) {
    if(*pit < 0 || *pit > l.size()) { continue; }
    size_t index = 1;
    for(std::list<int>::const_iterator lit = l.begin(); lit != l.end(); ++lit, ++index) {
      if(*pit == index) {
        std::cout << *lit << ' ';
      }
    }
  }
}

int main() {

  std::list<int> l;
  std::list<int> p;

  l.push_front(8);
  l.push_back(6);
  l.push_back(4);
  l.push_back(7);
  l.push_back(3);
  l.push_back(1);

  p.push_back(5);
  p.push_back(2);
  p.push_back(6);
  p.push_back(7); // skips this one
  p.push_back(4);

  printLots(l, p);

  std::cin.get();
  return 0;
}