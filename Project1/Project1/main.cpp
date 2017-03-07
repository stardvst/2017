#include <iostream>
#include <numeric>
#include <vector>
#include <tuple>


std::tuple<int, int, int> find_max_crossing_subarray(
  const std::vector<int>& A, int low, int mid, int high) {
  int left_sum = std::numeric_limits<int>::min();
  int sum = 0;
  int max_left;
  for(auto i = mid; i >= low; --i) {
    sum += A[i];
    if(sum > left_sum) {
      left_sum = sum;
      max_left = i;
    }
  }

  int right_sum = std::numeric_limits<int>::min();
  sum = 0;
  int max_right;
  for(auto j = mid + 1; j <= high; ++j) {
    sum += A[j];
    if(sum > right_sum) {
      right_sum = sum;
      max_right = j;
    }
  }

  return std::make_tuple(max_left, max_right, left_sum + right_sum);
}


std::tuple<int, int, int> find_max_subarray(
  const std::vector<int>& A, int low, int high) {
  if(high == low) {
    return std::make_tuple(low, high, A[low]);
  }

  int mid = low + (high - low) / 2;
  std::tuple<int, int, int> left = find_max_subarray(A, low, mid);
  std::tuple<int, int, int> right = find_max_subarray(A, mid + 1, high);
  std::tuple<int, int, int> cross = find_max_crossing_subarray(A, low, mid, high);

  if(std::get<2>(left) >= std::get<2>(right) && std::get<2>(left) >= std::get<2>(cross)) {
    return left;
  } else if(std::get<2>(right) >= std::get<2>(left) && std::get<2>(right) >= std::get<2>(cross)) {
    return right;
  } else {
    return cross;
  }
}



int main() {

  std::vector<int> A;

  int size = 0;
  while(size <= 0) {
    std::cout << "enter vector size: ";
    std::cin >> size;
  }

  for(auto i = 0; i < size; ++i) {
    int current;
    std::cout << "A[" << i << "] = ";
    std::cin >> current;
    A.push_back(current);
  }

  std::tuple<int, int, int> max = find_max_subarray(A, 0, static_cast<int>(A.size() - 1));

  std::cout << "\nmax sum: " << std::get<2>(max)
    << ", residing between indices " << std::get<0>(max)
    << " and " << std::get<1>(max) << std::endl;


  std::cin.get();
  std::cin.get();
  return 0;
}
