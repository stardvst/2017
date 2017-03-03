#include <iostream>
#include <vector>


void selection_sort(std::vector<int>& A) {
  for(int i = 0; i < A.size() - 1; ++i) {
    int min = i;

    for(int j = i + 1; j < A.size(); ++j) {
      if(A[j] < A[min]) {
        min = j;
      }
    }

    int tmp = A[i];
    A[i] = A[min];
    A[min] = tmp;
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

  selection_sort(A);

  std::cout << "\nsorted array: ";
  for(int i = 0; i < 7; ++i) {
    std::cout << A[i] << ' ';
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
