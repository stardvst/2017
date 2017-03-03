#include <iostream>
#include <vector>


void insertion_sort(std::vector<int>& A) {
  for(int i = 1; i < A.size(); ++i) {
    int key = A[i];
    int j = i - 1;

    while(j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      j = j - 1;
    }

    A[j + 1] = key;
  }
}


int main() {

  std::vector<int> A;

  for(int i = 0; i < 7; ++i) {
    int current;
    std::cout << "A[" << i << "] = ";
    std::cin >> current;
    A.push_back(current);
  }

  insertion_sort(A);

  std::cout << "\nsorted array: ";
  for(int i = 0; i < 7; ++i) {
    std::cout << A[i] << ' ';
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
