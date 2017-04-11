#include <iostream>
#include <vector>
#include <list>


void INSERTION_SORT(std::list<double>& B) {
  std::vector<double> A;
  for(std::list<double>::const_iterator it = B.begin(); it != B.end(); ++it) {
    A.push_back(*it);
  }

  for(int i = 1; i < A.size(); ++i) {
    double key = A[i];
    int j = i - 1;

    while(j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      j = j - 1;
    }

    A[j + 1] = key;
  }

  B.clear();
  for(int i = 0; i < A.size(); ++i) {
    B.push_back(A[i]);
  }
}

void BUCKET_SORT(std::vector<double>& A) {
  std::vector<std::list<double> > B(A.size());
  const size_t size = A.size();

  for(size_t i = 0; i < size; ++i) {
    int index = static_cast<int>(size * A[i]);
    B[index].push_back(A[i]);
  }

  for(size_t i = 0; i < size; ++i) {
    INSERTION_SORT(B[i]);
  }

  A.clear();
  for(size_t i = 0; i < size; ++i) {
    for(std::list<double>::const_iterator it = B[i].begin(); it != B[i].end(); ++it) {
      A.push_back(*it);
    }
  }
}

int main() {

  int number = 0;
  while(number <= 0) {
    std::cout << "# of elements: ";
    std::cin >> number;
  }

  std::vector<double> A(number);

  for(int i = 0; i < number; ++i) {
    std::cout << "A[" << i << "] = ";
    std::cin >> A[i];
  }

  BUCKET_SORT(A);

  for(int i = 0; i < number; ++i) {
    std::cout << A[i] << ' ';
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
