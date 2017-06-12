#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


int get_col(const std::vector<int>& matrix_row0, int key) {
    int low = 0;
    int high = static_cast<int>(matrix_row0.size()) - 1;
    int col1 = 0;
    int col2 = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(matrix_row0[mid] == key) {
            return mid;
        }
        if(matrix_row0[mid] < key) {
            col1 = mid;
            low = mid + 1;
        } else if(matrix_row0[mid] > key) {
            col2 = mid;
            high = mid - 1;
        }
    }
    return col1;
}

int get_row(const std::vector<std::vector<int> >& matrix, int col, int key) {
    int low = 0;
    int high = static_cast<int>(matrix[0].size()) - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        int element = matrix[mid][col];
        if(element == key) {
            return mid;
        }
        if(element < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

std::pair<int, int> get_indices(const std::vector<std::vector<int> >& matrix, int key) {
    int col = get_col(matrix[0], key);
    int row = get_row(matrix, col, key);

    if(row != -1) {
        return std::make_pair(row, col);
    }
    return std::make_pair(-1, -1);
}


int main() {
    
    std::ifstream file;
    file.open("matrix.txt");

    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        std::vector<std::vector<int> > matrix;
       
        std::string row;
        while(std::getline(file, row)) {
            matrix.emplace_back(std::vector<int>());

            int number;
            std::size_t size = matrix.size() - 1;
            std::istringstream iss(row);
            while(iss >> number) {
                matrix[size].emplace_back(number);
            }
        }

        int key;
        std::cout << "key: ";
        std::cin >> key;
        std::pair<int, int> indices = get_indices(matrix, key);
        std::cout << "i:" << indices.first << ", j: " << indices.second << std::endl;
    }

    std::cin.get();
    std::cin.get();
    return 0;
}
