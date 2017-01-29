#include <iostream>
#include <list>

int josephus_problem(std::list<int>& people, int m) {
  std::list<int>::iterator person = people.begin();
  while(people.size() > 1) {
    for(int i = 0; i < m; ++i) {
      if(*person == people.back()) {
        person = people.begin();
      } else {
        ++person;
      }
    }
    if(*person == people.back()) {
      std::cout << "deleting " << *person << '\n';
      people.erase(person);
      person = people.begin();
    } else {
      std::cout << "deleting " << *person << '\n';
      person = people.erase(person);
    }
  }
  return *(people.begin());
}

int main() {
  
  int n;
  std::cout << "n = ";
  std::cin >> n;

  std::list<int> people;
  for(int i = 1; i <= n; ++i) {
    people.push_back(i);
  }

  int m;
  std::cout << "m = ";
  std::cin >> m;
  std::cout << '\n';

  std::cout << "\nwinner: " << josephus_problem(people, m);


  std::cin.get();
  std::cin.get();
  return 0;
}