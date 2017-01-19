#include <iostream>
#include <string>
#include <vector>
#include <functional>


template<typename T, typename Comparator>
const T& find_max(const std::vector<T>& v, Comparator is_less_than) {
  int max_index = 0;

  for(size_t i = 1; i < v.size(); ++i) {
    if(is_less_than(v[max_index], v[i])) {
      max_index = i;
    }
  }

  return v[max_index];
}

template<typename T> // using default ordering
const T& find_max(const std::vector<T>& v) {
  return find_max(v, std::less<T>());
}


class case_sensitive_cmp {
public:
  bool operator()(const std::string& lhs, const std::string& rhs) {
    return _stricmp(lhs.c_str(), rhs.c_str()) < 0;
  }
};

int main() {

  std::vector<std::string> v(3);
  v[0] = "ZEBRA";
  v[1] = "alligator";
  v[2] = "crocodile";

  std::cout << find_max(v, case_sensitive_cmp()) << std::endl;
  std::cout << find_max(v);
 
  std::cin.get();
  return 0;
}