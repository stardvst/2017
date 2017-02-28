#include <iostream>
#include <vector>


size_t merge_and_count(std::vector<int>& arr, 
                       std::vector<int>& tmp,
                       size_t low, size_t mid, size_t high) {
  size_t i = low;
  size_t j = mid + 1;
  size_t k = low;

  size_t count = 0;

  while(i <= mid && j <= high) {
    if(arr[i] <= arr[j]) {
      tmp[k++] = arr[i++];
    } else {
      tmp[k++] = arr[j++];
      count += mid + 1 - i;
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

  return count;
}

size_t sort_and_count(std::vector<int>& arr, 
                      std::vector<int>& tmp, 
                      size_t low, size_t high) {
  if(low < high) {
    size_t mid = low + (high - low) / 2;

    size_t X = sort_and_count(arr, tmp, low, mid);
    size_t Y = sort_and_count(arr, tmp, mid + 1, high);
    size_t Z = merge_and_count(arr, tmp, low, mid, high);

    return X + Y + Z;
  }

  return 0;
}

size_t sort_and_count(std::vector<int>& arr) {
  std::vector<int> tmp(arr.size());
  return sort_and_count(arr, tmp, 0, arr.size() - 1);
}


int main() {

  std::vector<int> arr;

  int number = 0;
  while(number <= 0) {
    std::cout << "enter number of elements: ";
    std::cin >> number;
  }

  int current;
  for(int i = 0; i < number; ++i) {
    std::cout << "arr[0] = ";
    std::cin >> current;
    arr.push_back(current);
  }

  std::cout << "\narr: ";
  for(std::vector<int>::const_iterator it = arr.begin(); it != arr.end(); ++it) {
    std::cout << *it << " ";
  }
  
  std::cout << "\n\nnumber of inversions: " << sort_and_count(arr);


  std::cin.get();
  std::cin.get();
}



