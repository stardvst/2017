#include <iostream>
#include <string>
using namespace std;


std::string lucky(int N) {
    int mirror = 0;
    while(N) {

        int rem = N % 10;
        if(rem != 1 && rem != 8 && rem != 0) {
            return "NO";
        }

        mirror = mirror * 10 + N % 10;
        N /= 10;
    }


    return "YES";
}

int main() {

    int T;
    cout << "T = ";
    cin >> T;

    int N;
    for(int i = 0; i < T; ++i) {
        cout << "N = ";
        cin >> N;
        cout << lucky(N) << endl;
    }

    std::cin.get();
    return 0;
}
