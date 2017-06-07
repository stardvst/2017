#include <iostream>
#include <vector>
#include <random>


int RANDOM_SEARCH(const std::vector<int>& A, int x) {
    const int n = static_cast<int>(A.size());
    std::vector<bool> C(n, false);
    int picked = 0;
    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<> dist(0, n - 1);
    while(true) {
        int i = dist(mt);
        if(C[i] == false) {
            C[i] = true;
            ++picked;
            if(picked == n) {
                return -1;
            } else if(A[i] == x) {
                return i;
            }
        }
    }
}


int main() {

    std::vector<int> A { 3,1,6,8,7,5,3 };
    std::cout << RANDOM_SEARCH(A, 3);
    
    std::cin.get();
    return 0;
}