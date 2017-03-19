#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>


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

int randomized_partition(std::vector<int>& A, int low, int high) {
  std::srand(static_cast<unsigned int>(std::time(0)));
  int i = std::rand() % (high - low + 1) + low;
  std::swap(A[i], A[high]);
  return partition(A, low, high);
}

void randomized_quicksort(std::vector<int>& A, int low, int high) {
  if(low < high) {
    int q = randomized_partition(A, low, high);
    randomized_quicksort(A, low, q - 1);
    randomized_quicksort(A, q + 1, high);
  }
}



int main() {

  std::vector<int> A;

  for(int i = 0; i < 10; ++i) {
    int current;
    std::cout << "A[" << i << "] = ";
    std::cin >> current;
    A.push_back(current);
  }

  randomized_quicksort(A, 0, static_cast<int>(A.size() - 1));

  std::cout << "\nsorted array: ";
  for(int i = 0; i < 10; ++i) {
    std::cout << A[i] << ' ';
  }

  std::cin.get();
  std::cin.get();
  return 0;
}
