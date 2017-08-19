#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <list>

std::vector<int> pigeonhole_sort(const std::vector<int> &v) {
    int min = v.at(0);
    int max = min;
    std::size_t i = 1;

    const std::size_t size = v.size();
    if(size % 2 == 0) {
        max = std::max(min, v.at(1));
        min = std::min(min, v.at(1));
        i = 2;
    }

    for(; i < size - 1; i += 2) {
        int current_min = std::min(v.at(i), v.at(i + 1));
        int current_max = std::max(v.at(i), v.at(i + 1));
        if(current_min < min)
            min = current_min;
        else if(current_max > max)
            max = current_max;
    }

    const int range = max - min + 1;

    std::vector<std::list<int> > holes(range);
    for(i = 0; i < size; ++i) {
        int current = v.at(i);
        holes.at(current - min).push_back(current);
    }

    std::vector<int> result;
    for(std::vector<std::list<int> >::const_iterator it = holes.begin(); it != holes.end(); ++it) {        
        std::list<int> list = *it;
        if(list.empty())
            continue;

        for(std::list<int>::const_iterator it2 = list.begin(); it2 != list.end(); ++it2) {
            result.push_back(*it2);
        }
    }

    return result;
}

int main() {
    
    std::vector<int> v = { -4, 7, 4, 2, 5, 3, 1, 9, 0, -5 };
    std::vector<int> sorted = pigeonhole_sort(v);
    
    std::copy(sorted.begin(), sorted.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cin.get();
}