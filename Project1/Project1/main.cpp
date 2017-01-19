#include <iostream>
#include <string>
#include <vector>


class Employee {
public:
  void set_value(const std::string& n, double s) { name = n; salary = s; }
  const std::string& get_name() const { return name; }
  void print(std::ostream& out) const { out << name << " (" << salary << ")";+ }
  bool operator<(const Employee& rhs) const { return salary < rhs.salary; }
private:
  std::string name;
  double salary;
};

std::ostream& operator<<(std::ostream& out, const Employee& rhs) {
  rhs.print(out);
  return out;
}

template<typename T>
const T& find_max(const std::vector<T>& v) {
  int max_index = 0;

  for(size_t i = 1; i < v.size(); ++i) {
    if(v[max_index] < v[i]) {
      max_index = i;
    }
  }

  return v[max_index];
}

int main() {

  std::vector<Employee> v(3);

  v[0].set_value("George Bush", 400000.00);
  v[1].set_value("Bill Gates", 2000000000.00);
  v[0].set_value("Dr. Pill", 13000000.00);
  std::cout << find_max(v) << std::endl;


 
  std::cin.get();
  return 0;
}