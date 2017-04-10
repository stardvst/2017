#include <algorithm>
#include <iostream>
#include <vector>


int get_max(const std::vector<int>& A) {
  int max = A[0];
  for(size_t i = 1; i < A.size(); ++i) {
    if(A[i] > max) {
      max = A[i];
    }
  }
  return max;
}

void COUNTING_SORT(std::vector<int>& A, int exp) {
  
  std::vector<int> B(A.size()); 
  std::vector<int> C(10);

  for(size_t i = 0; i < A.size(); ++i) {
    ++C[(A[i] / exp) % 10];
  }

  for(int i = 1; i < 10; ++i) {
    C[i] += C[i - 1];
  }

  for(int i = static_cast<int>(A.size()) - 1; i >= 0; --i) {
    B[C[(A[i] / exp) % 10] - 1] = A[i];
    --C[(A[i] / exp) % 10];
  }

  std::swap_ranges(A.begin(), A.end(), B.begin());
}

void RADIX_SORT(std::vector<int>& A) {
  int max = get_max(A);
  for(int exp = 1; max / exp > 0; exp *= 10) {
    COUNTING_SORT(A, exp);
  }
}


int main() {

  int number = 0;
  while(number <= 0) {
    std::cout << "# of elements: ";
    std::cin >> number;
  }

  std::vector<int> A(number);

  for(int i = 0; i < number; ++i) {
    std::cout << "A[" << i << "] = ";
    std::cin >> A[i];
  }

  RADIX_SORT(A);

  for(int i = 0; i < number; ++i) {
    std::cout << A[i] << ' ';
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
