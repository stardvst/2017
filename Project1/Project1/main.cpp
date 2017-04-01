#include <iostream>


class G {};
class M : virtual public G {};
class P : virtual public G {};
class m : public M, public P, virtual public G {};


int main() {

  m* me = new m();
  me;

  std::cin.get();
  return 0;
}
