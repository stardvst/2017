#include <iostream>
#include <string>
#include <vector>

class case_insensitive_cmp {
public:
  bool is_less_than(const std::string& lhs, const std::string& rhs) {
    return _stricmp(lhs.c_str(), rhs.c_str()) < 0;
  }
};

template<typename T, typename Comparator>
const T& find_max(const std::vector<T>& v, Comparator cmp) {
  int max_index = 0;

  for(size_t i = 1; i < v.size(); ++i) {
    if(cmp.is_less_than(v[max_index], v[i])) {
      max_index = i;
    }
  }

  return v[max_index];
}

int main() {

  std::vector<std::string> v(3);
  v[0] = "ZEBRA";
  v[1] = "alligator";
  v[2] = "crocodile";

  std::cout << find_max(v, case_insensitive_cmp());

 
  std::cin.get();
  return 0;
}