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

        int q1 = static_cast<int>(0.25 * v.size());
        int q3 = static_cast<int>(0.75 * v.size());

        std::nth_element(v.begin(), v.begin() + q1, v.end());
        std::cout << "Q1: " << v[q1];
        std::nth_element(v.begin() + q1, v.begin() + q3, v.end());
        std::cout << "\nQ3: " << v[q3];

        file.close();
    }

    std::cin.get();
    return 0;
}