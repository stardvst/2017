#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <iostream>
#include <limits>


template<typename T>
struct Visitor {};


template<typename T>
struct Print : Visitor<T> {
  void operator()(const T& value) const {
    std::cout << value << ' ';
  }
};


template<typename T>
struct Max : private Visitor<T> {
public:
  Max() : max(std::numeric_limits<T>::min()) {}
  void operator()(const T& value) const {
    max = (value > max) ? value : max;
  }
  mutable T max;
};


template<typename T>
struct Sum : Visitor<T> {
public:
  Sum() : sum(0) {}
  void operator()(const T& value) const {
    sum += value;
  }
  mutable T sum;
};


#endif // !VISITOR_HPP
