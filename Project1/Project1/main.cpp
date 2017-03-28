#include <iostream>
#include <vector>
#include <string>


int main() {

  std::string str1;
  std::string str2;
  
  std::cout << "str1: ";
  std::cin >> str1;
  std::cout << "str2: ";
  std::cin >> str2;


  std::vector<int> count(26);

  for(size_t i = 0; i < str1.length(); ++i) {
    ++count[str1[i] - 'a'];
  }

  for(size_t i = 0; i < str2.length(); ++i) {
    --count[str2[i] - 'a'];
  }

  int symbol_count = 0;
  for(size_t i = 0; i < count.size(); ++i) {
    symbol_count += std::abs(count[i]);
  }

  std::cout << "remove " << symbol_count << " symbols\n";

  std::cin.get();
  std::cin.get();
}
