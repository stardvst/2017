#include <iostream>
#include <vector>
#include <ctime>

void merge(std::vector<int>& arr, std::vector<int>& tmp, size_t low, size_t mid, size_t high) {

  size_t i = low;
  size_t j = mid + 1;
  size_t  k = low;

  while(i <= mid && j <= high) {
    if(arr[i] <= arr[j]) {
      tmp[k++] = arr[i++];
    } else {
      tmp[k++] = arr[j++];
    }
  }

  while(i <= mid) {
    tmp[k++] = arr[i++];
  }
  while(j <= high) {
    tmp[k++] = arr[j++];
  }

  for(size_t t = low; t <= high; ++t) {
    arr[t] = tmp[t];
  }
}

void merge_sort(std::vector<int>& arr, std::vector<int>& tmp, size_t low, size_t high) {
  if(low < high) {
    size_t mid = low + (high - low) / 2; // same as (low + high)/2 but safer (won't overflow)
    merge_sort(arr, tmp, low, mid); 
    merge_sort(arr, tmp, mid + 1, high);
    merge(arr, tmp, low, mid, high);
  }
}

void merge_sort(std::vector<int>& arr) {
  std::vector<int> tmp(arr.size());
  merge_sort(arr, tmp, 0, arr.size() - 1);
}

int main() {

  srand(static_cast<unsigned>(time(NULL)));

  std::vector<int> arr;
  for(int i = 0; i < 12; ++i) {
    arr.push_back(rand() % 12 + 1);
  }
  for(std::vector<int>::const_iterator it = arr.begin(); it != arr.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  merge_sort(arr);
  for(std::vector<int>::const_iterator it = arr.begin(); it != arr.end(); ++it) {
    std::cout << *it << " ";
  }


  std::cin.get();
}