#include <iostream>
#include <vector>


void insertion_sort(std::vector<int>& A, int index) {
  if(index == 0) return;

  insertion_sort(A, index - 1);

  int key = A[index];
  while(index - 1 >= 0 && A[index - 1] > key) {
    A[index] = A[index - 1];
    index = index - 1;
  }
  A[index] = key;
}


int binary_search(const std::vector<int>& A, int key, int start, int end) {
  if(start <= end) {
    int mid = (start + end) / 2;
    if(key == A[mid]) return mid;

    if(key > A[mid]) {
      return binary_search(A, key, mid + 1, end);
    } else {
      return binary_search(A, key, start, mid - 1);
    }
  }

  return -1;
}

int binary_search(const std::vector<int>& A, int key) {
  int start = 0;
  int end = static_cast<int>(A.size());

  while(start <= end) {
    int mid = (start + end) / 2;

    if(key == A[mid]) return mid;

    if(key > A[mid]) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  return -1;
}


int main() {

  std::vector<int> A;

  int number = 0;
  while(number <= 0) {
    std::cout << "enter the numbers of the array: ";
    std::cin >> number;
  }
  for(int i = 0; i < number; ++i) {
    int current;
    std::cout << "A[" << i << "] = ";
    std::cin >> current;
    A.push_back(current);
  }

  insertion_sort(A, number - 1);

  std::cout << "\nsorted array: ";
  for(int i = 0; i < number; ++i) {
    std::cout << A[i] << ' ';
  }

  int key;
  std::cout << "\n\nenter a key to search for: ";
  std::cin >> key;
  std::cout << key << " is at index " << binary_search(A, key, 0, number - 1) << 
    " (recursive), " << binary_search(A, key) << " (iterative)";

  std::cin.get();
  std::cin.get();
  return 0;
}
