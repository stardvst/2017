#include <iostream>
#include <vector>


void COUNTING_SORT(const std::vector<int> A, std::vector<int>& B, int k) {
  std::vector<int> C(k + 1); // C contains 0s

  for(size_t i = 0; i < A.size(); ++i) {
    ++C[A[i]];
  }

  for(int i = 1; i <= k; ++i) {
    C[i] += C[i - 1];
  }

  for(int i = static_cast<int>(A.size()) - 1; i >= 0; --i) {
    B[C[A[i]] - 1] = A[i];
    --C[A[i]];
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

  int k = 0;
  while(k <= 0) {
    std::cout << "\nrange: 0 - ";
    std::cin >> k;
  }

  std::vector<int> B(number);

  COUNTING_SORT(A, B, k);


  for(int i = 0; i < number; ++i) {
    std::cout << B[i] << ' ';
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
