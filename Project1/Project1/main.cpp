#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


int main() {

  std::vector<int> vi;

  int n;
  std::cout << "enter n: ";
  std::cin >> n;
  n = (int)n;
  
  int k = n / 2;

  std::cout << '\n';

  int item;
  for(int i = 0; i < k; ++i) {
    std::cout << "enter item " << i + 1 << ": ";
    std::cin >> item;
    vi.push_back(item);
  }
  std::sort(vi.begin(), vi.end(), [](int a, int b) {return a > b; });

  for(int i = 0; i < k; ++i) {
    std::cout << "enter another item: ";
    std::cin >> item;
    if(item > vi[k - 1]) {
      vi.erase(vi.begin() + k-1);
      vi.push_back(item);
      std::sort(vi.begin(), vi.end(), [](int a, int b) {return a > b; });
    }
  }

  std::cout << vi[k-1];


  std::cin.get();
  std::cin.get();
  return 0;
}