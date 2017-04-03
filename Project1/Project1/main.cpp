#include <iostream>


class Data {
public:
  Data() : n(0) { std::cout << "Data"; }
  ~Data() { std::cout << "~Data"; }
private:
  int n;
};

class Base {
public:
  Base() { std::cout << "Base"; }
  ~Base() { std::cout << "~Base"; }
private:
  Data b;
};

class Der : public Base {
public:
  Der() { std::cout << "Der"; }
  ~Der() { std::cout << "~Der"; }
private:
  Data d;
};

int main() {

  Base* b = new Der(); // DataBaseDataDer~Base~Data
  // Der* b = new Der(); // DataBaseDataDer~Der~Data~Base~Data
  delete b;

  std::cin.get();
  return 0;
}