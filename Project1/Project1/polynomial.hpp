#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <iostream>


struct Term {
  int coeff;
  int exp;
  Term* next;

  Term(int c = 0, int e = 0, Term* n = NULL) : coeff(c), exp(e), next(n) {}
};


class Polynomial {
  friend std::ostream& operator<<(std::ostream&, const Polynomial&);
  friend Polynomial operator+(const Polynomial&, const Polynomial&);
  friend Polynomial operator-(const Polynomial&, const Polynomial&);
public:
  Polynomial();
  Polynomial(const Polynomial&);
  ~Polynomial();
  
  void add_term(int, int);
private:
  Term* first;
};


#endif // !POLYNOMIAL_HPP
