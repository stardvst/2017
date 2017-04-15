#ifndef ELEMENT_HPP
#define ELEMENT_HPP


template<typename T>
struct Element {
  T value;
  int left;
  int right;

  Element(T v = T(), int l = -1, int r = -1) : value(v), left(l), right(r) {}
};

#endif // !ELEMENT_HPP
