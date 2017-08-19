#include <iostream>

struct Point {
    int x;
    int y;
};

bool do_overlap(const Point &l1, const Point &r1, const Point &l2, const Point &r2) {
    if(l1.x > r2.x || l2.x > r1.x) // if one rectangle is on left side of the other
        return false;

    if(l1.y < r2.y || l2.y < r1.y) // if one rectangle is above the other
        return false;

    return true;
}

int main() {
    
    std::cout << do_overlap({ 1,5 }, { 6,1 }, { 4,8 }, { 9,4 });

    std::cin.get();
}