#include <iostream>
#include <vector>


template<typename T>
class matrix {
public:
  matrix(int rows, int cols) : arr(rows) {
    for(int i = 0; i < rows; ++i) {
      arr[i].resize(cols);
    }
  }

  const std::vector<T>& operator[](int row) const { return arr[row]; }
  std::vector<T>& operator[](int row) { return arr[row]; }

  int numrows() { return arr.size(); }
  int numcols() { return numrows() ? arr[0].size() : 0; }
private:
  std::vector<std::vector<T> > arr;
};

void copy(const matrix<int>& from, matrix<int>& to) {
  for(int i = 0; i < to.numrows(); ++i) {
    to[i] = from[i];
  }
}
// to[i]    - operator[]
// from[i]  - const operator[] const

int main() {
 
  std::cin.get();
  return 0;
}