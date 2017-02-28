#include <iostream>
#include <vector>
#include <string>


int chars(const std::string& str1, const std::string& str2) {
  std::vector<int> occurences(26);

  for(size_t i = 0; i < str1.length(); ++i) {
    occurences[str1[i] - 'a']++;
  }

  for(size_t i = 0; i < str2.length(); ++i) {
    occurences[str2[i] - 'a']--;
  }

  int sum = 0;
  for(std::vector<int>::const_iterator i = occurences.begin();
      i != occurences.end(); ++i) {
    sum += std::abs(*i);
  }

  return sum;
}

int main() {

  std::string str1;
  std::cout << "enter str1: ";
  std::cin >> str1;

  std::string str2;
  std::cout << "enter str2: ";
  std::cin >> str2;

  std::cout << '\n' << chars(str1, str2) << " chars to remove to make \"" <<
    str1 << "\" and \"" << str2 << "\" anagrams";

  std::cin.get();
  std::cin.get();
}



