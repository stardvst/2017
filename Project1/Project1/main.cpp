#include <iostream>
#include <vector>


int partition(std::vector<int>& A, int low, int high) {
  int pivot = A[high];
  int i = low - 1;
  for(int j = low; j < high; ++j) {
    if(A[j] <= pivot) {
      ++i;
      std::swap(A[i], A[j]);
    }
  }
  std::swap(A[i + 1], A[high]);
  return i + 1;
}


void quicksort(std::vector<int>& A, int low, int high) {
  if(low < high) {
    int q = partition(A, low, high);
    quicksort(A, low, q - 1);
    quicksort(A, q + 1, high);
  }
}


int main() {

  std::vector<int> A;

  for(int i = 0; i < 6; ++i) {
    int current;
    std::cout << "A[" << i << "] = ";
    std::cin >> current;
    A.push_back(current);
  }

  quicksort(A, 0, static_cast<int>(A.size() - 1));

  std::cout << "\nsorted array: ";
  for(int i = 0; i < 6; ++i) {
    std::cout << A[i] << ' ';
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
