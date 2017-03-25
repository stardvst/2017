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

// recursive
int randomized_select(std::vector<int>& A, int low, int high, int i) {
  if(low == high) {
    return A[low];
  }
  int q = randomized_partition(A, low, high);
  int k = q - low + 1;
  if(i == k) {
    return A[q];
  } else if(i < k) {
    return randomized_select(A, low, q - 1, i);
  } else {
    return randomized_select(A, q + 1, high, i - k);
  }
}

// iterative
int randomized_select_iter(std::vector<int>& A, int low, int high, int i) {
  while(low < high - 1) {
    int q = randomized_partition(A, low, high);
    int k = q - low + 1;
    if(i == k) {
      return A[q];
    } else if(i < k) {
      high = q;
    } else {
      low = q + 1;
      i = i - k;
    }
  }
  return A[low];
}



int main() {

  std::vector<int> A;

  for(int i = 0; i < 10; ++i) {
    int current;
    std::cout << "A[" << i << "] = ";
    std::cin >> current;
    A.push_back(current);
  }

  int i;
  std::cout << "enter i: ";
  std::cin >> i;

  std::cout << "\nith order statistics - "
    << "recursive: " << randomized_select(A, 0, static_cast<int>(A.size() - 1), i) << ", "
    << "iterative: " << randomized_select_iter(A, 0, static_cast<int>(A.size() - 1), i)
    << std::endl;

  std::cin.get();
  std::cin.get();
  return 0;
}

