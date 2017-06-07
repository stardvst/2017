#include <iostream>
#include <vector>


void COMPARE_EXCHANGE(std::vector<int>& A, int i, int j) {
    if(A[i] > A[j]) {
        std::swap(A[i], A[j]);
    }
}

void INSERTION_SORT(std::vector<int>& A) {
    const int size = static_cast<int>(A.size());
    for(int j = 2; j < size; ++j) {
        for(int i = j - 1; i >= 0; --i) {
            COMPARE_EXCHANGE(A, i, i + 1);
        }
    }
}


int main() {

    std::vector<int> A { 3,1,6,8,7,5,3 };
    INSERTION_SORT(A);
    for(std::size_t i = 0; i < 7; ++i) {
        std::cout << A[i] << ' ';
    }
    
    std::cin.get();
    return 0;
}