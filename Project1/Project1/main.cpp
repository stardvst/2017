//#include <iostream>
//#include <fstream>
//#include "quicksort.hpp"
//
//
//int main() {
//
//  std::ifstream file;
//  file.open("numbers.txt");
//  
//  Quicksort<int> q(file);
//  file.close();
//
//  q.multi_threaded();
//  q.print();
//  
//  std::cin.get();
//  return 0;
//}

//
//#include <iostream>
//#include "red_black_tree.hpp"
//#include "Node.hpp"
//#include <set>
//
//
//int main() {
//
//    RedBlackTree<int> rbt;
//    rbt.insert(7);
//    rbt.insert(11);
//    rbt.insert(20);
//    rbt.insert(40);
//    rbt.insert(15);
//    rbt.insert(45);
//
//    rbt.remove(15);
//
//
//    std::cin.get();
//    return 0;
//}


#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


int main() {

    std::ifstream file;
    file.open("numbers.txt");


    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        std::vector<int> v;

        int value;
        while(file >> value) {
            v.push_back(value);
        }

        int n = 0;
        while(n <= 0 || n > 100) {
            std::cout << "calculating nth percentile, n = ";
            std::cin >> n;
        }

        std::nth_element(v.begin(), v.begin() + n * v.size() / 100, v.end());
        std::cout << "nth percentile: " << v[n * v.size() / 100];

        file.close();
    }

    std::cin.get();
    std::cin.get();
    return 0;
}