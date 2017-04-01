#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <list>


int main() {

  typedef std::list<int> L;
  L l(5);

  typedef L::const_iterator CI;
  CI cb = l.begin(), ce = l.end();

  typedef L::iterator I;
  I b = l.begin();

  std::transform(cb, --ce, // input range
    ++b, // output range
    std::bind2nd(std::plus<CI::value_type>(), 1) // what to do
  );

  std::copy(l.begin(), l.end(),
            std::ostream_iterator<CI::value_type>(std::cout));

  std::cin.get();
  return 0;
}
