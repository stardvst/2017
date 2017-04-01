#include <iostream>


struct Exc1 {
  void what() { std::cout << "Exc1" << std::endl; }
};

struct Exc2 : public Exc1 {
  void what() { std::cout << "Exc2" << std::endl; }
};


int main() {

  try {
    throw Exc2();
  }
  /*catch(Exc1& e) {
    std::cout << "1st catch: "; // Exc2& is caught by base class
    e.what();
  }*/
  catch(Exc2& e) {
    std::cout << "2nd catch: ";
    e.what();
  } catch(...) {
    std::cout << "unknown exception\n";
  }

  std::cin.get();
  return 0;
}
