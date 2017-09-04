#ifndef LIST_TESTS_H
#define LIST_TESTS_H

#include <string>
#include <limits>

#include "list.h"

template<typename T>
void print(const List<T> &list) {
    std::cout << "\nlist:\thead -> ";
    typename List<int>::Iterator it = list.begin();
    while(it != list.end()) {
        std::cout << *it << " -> ";
        ++it;
    }
    std::cout << "nullptr\n";
}

template<typename T>
void test_operations(List<T> &list) {
    
    test_clear(list);
    print(list);

    // clear the ctrl+z / ctrl+d from the stream
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max() + 1, '\n');

    test_push(list); // push back
    print(list);

    test_push(list, false); // push_front
    print(list);

    test_pop(list); // pop_back, pop_front
    print(list);

    test_erase(list, false); // try to remove a value that isn't in the list
    print(list);

    test_erase(list); // remove a value that is in the list
    print(list);

    test_size(list); // size and emptiness

    test_iterator(list); // insert in list using iterator
    print(list);
}

template<typename T>
void test_clear(List<T> &list) {
    std::cout << "list.clear()";
    list.clear();
}

template<typename T>
void test_push(List<T> &list, const bool back = true) {
    T input1 = T();
    T input2 = T();

    std::cout << "\n-------------------------------------------\n\n";
    std::cout << "enter values to push_" << (back ? "back" : "front") << "()\n";
        
    std::cout << "input1: ";
    std::cin >> input1;
    std::cout << "input2: ";
    std::cin >> input2;

    std::cout << "\nlist.push_" << (back ? "back" : "front") << '(' << input1 << ')' <<
        "\nlist.push_" << (back ? "back" : "front") << '(' << input2 << ")";
    
    if(back) {
        list.push_back(input1);
        list.push_back(input2);
    } else {
        list.push_front(input1);
        list.push_front(input2);
    }
}

template<typename T>
void test_pop(List<T> &list) {
    std::cout << "\npress enter to execute the next operation...";
    std::string dummy;
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, dummy);

    std::cout << "\n-------------------------------------------\n\n";
    std::cout << "list.pop_back()\nlist.pop_front()\n";

    list.pop_back();
    list.pop_front();
}

template<typename T>
void test_erase(List<T> &list, const bool exists = true) {
    std::cout << "\n-------------------------------------------\n";
    print(list);
    
    T input = T();
    std::cout << "\nenter a value that " << (exists ? "is" : "isn't") << " in the list: ";
    std::cin >> input;

    std::cout <<
        "\nlist.erase(" << input << ")"
        "\ndid erase() remove it? "
        << std::boolalpha << (list.erase(input) ? "yes" : "no") << '\n';
}

template<typename T>
void test_size(const List<T> &list) {
    std::cout << "\n-------------------------------------------\n";
    print(list);
    std::cout <<
        "\nlist.size() == " << list.size() <<
        "\nlist.empty()? " << std::boolalpha << (list.empty() ? "yes" : "no");
}

template<typename T>
void test_iterator(List<T> &list) {
    std::cout << "\n\n-------------------------------------------\n\n";
    
    T input = T();
    std::cout << "enter a value to insert at list.begin(): ";
    std::cin >> input;

    std::cout << "list.insert(list.begin(), " << input << ')';
    list.insert(list.begin(), input);
}

#endif // !LIST_TESTS_H
