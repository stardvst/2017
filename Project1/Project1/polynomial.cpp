#include <iostream>
#include <cmath>
#include "polynomial.hpp"


Polynomial::Polynomial() : first(new Term()) {}

Polynomial::~Polynomial() {
  while(first) {
    Term* tmp = first;
    first = first->next;
    delete tmp;
  }
}

Polynomial::Polynomial(const Polynomial& p) {
  Term* p_tmp = p.first;
  Term* tmp = first = new Term;

  while(p_tmp) {
    tmp->next = new Term(p_tmp->coeff, p_tmp->exp);
    p_tmp = p_tmp->next;
    tmp = tmp->next;
  }
}

void Polynomial::add_term(int coeff, int exp) {
  Term* tmp = first;
  while(tmp->next && tmp->next->exp >= exp) {
    tmp = tmp->next;
  }
  if(tmp == first) {
    tmp->next = new Term(coeff, exp, tmp->next);
  } else if(tmp->exp == exp) {
    tmp->coeff += coeff;
  } else {
    tmp->next = new Term(coeff, exp, tmp->next);
  }
}


std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
  Term* tmp = p.first->next;
  int term_count = 0;

  while(tmp) {
    int coeff = tmp->coeff;
    if(coeff != 0) {
      if(coeff < 0) {
        if(term_count == 0) {
          out << "-";
        } else {
          out << " - ";
        }
      } else if(term_count > 0) {
        out << " + ";
      }
      
      if(coeff == 1 && tmp->exp == 0) {
        out << "1";
      }

      int abs_value = std::abs(coeff);
      if(abs_value != 1) {
        out << abs_value;
      }

      int exp = tmp->exp;
      if(exp != 0) {      
        out << "x";
        if(exp > 1) {
          out << "^" << exp;
        } else if(exp < 0) {
          out << "^(" << exp << ")";
        }
      }

      ++term_count;
    } else {
      tmp = tmp->next;
      continue;
    }

    tmp = tmp->next;
  }

  return out;
}


Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
  Polynomial result;

  Term* ptr1 = p1.first->next;
  Term* ptr2 = p2.first->next;
  Term* ptr = result.first;

  while(ptr1 && ptr2) {
    if(ptr1->exp > ptr2->exp) {
      ptr->next = new Term(ptr1->coeff, ptr1->exp);
      ptr1 = ptr1->next;
      ptr = ptr->next;
    } else if(ptr1->exp < ptr2->exp) {
      ptr->next = new Term(ptr2->coeff, ptr2->exp);
      ptr2 = ptr2->next;
      ptr = ptr->next;
    } else {
      if(ptr1->coeff + ptr2->coeff != 0) {
        ptr->next = new Term(ptr1->coeff + ptr2->coeff, ptr1->exp);
        ptr = ptr->next;
      }
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
    }
  }

  while(ptr1) {
    ptr->next = new Term(ptr1->coeff, ptr1->exp);
    ptr1 = ptr1->next;
    ptr = ptr->next;
  }
  while(ptr2) {
    ptr->next = new Term(ptr2->coeff, ptr2->exp);
    ptr2 = ptr2->next;
    ptr = ptr->next;
  }

  return result;
}


Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
  Polynomial result;

  Term* ptr1 = p1.first->next;
  Term* ptr2 = p2.first->next;
  Term* ptr = result.first;

  while(ptr1 && ptr2) {
    if(ptr1->exp > ptr2->exp) {
      ptr->next = new Term(ptr1->coeff, ptr1->exp);
      ptr1 = ptr1->next;
      ptr = ptr->next;
    } else if(ptr1->exp < ptr2->exp) {
      ptr->next = new Term(-ptr2->coeff, ptr2->exp);
      ptr2 = ptr2->next;
      ptr = ptr->next;
    } else {
      ptr->next = new Term(ptr1->coeff - ptr2->coeff, ptr1->exp);
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
      ptr = ptr->next;
    }
  }

  while(ptr1) {
    ptr->next = new Term(ptr1->coeff, ptr1->exp);
    ptr1 = ptr1->next;
    ptr = ptr->next;
  }
  while(ptr2) {
    ptr->next = new Term(-ptr2->coeff, ptr2->exp);
    ptr2 = ptr2->next;
    ptr = ptr->next;
  }

  return result;
}
