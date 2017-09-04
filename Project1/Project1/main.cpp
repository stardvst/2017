#include <iostream>

#include "list_tests.h"
#include "list.h"

int main() {

    List<int> list;

    std::cout << "enter list elements (ctrl+z or ctrl+d to exit):\n";
    
    // add user input to the list
    int current;
    while(std::cin >> current) {
        list.push_back(current);
    }

    // if the user provided input, print the list 
    if(!list.empty()) {
        print(list);
    }

    // test list operations
    std::cout << "\n\ntesting list operations...\n\n";
    test_operations(list);

    std::cout << std::endl;

    system("pause");
    return 0;
}