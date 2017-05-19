#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>


int main() {

    std::ifstream file;
    file.open("input.txt");

    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {

        std::vector<std::vector<float>> matrix;
        std::string line;
        while(std::getline(file, line)) {
            std::vector<float> row;
            std::istringstream iss(line);
            while(iss >> line) {
                row.push_back(std::stof(line));
            }
            matrix.push_back(row);
        }


        int step;
        std::cout << "step = ";
        std::cin >> step;

        std::size_t rows = matrix.size();
        std::size_t cols = matrix[0].size();
        std::size_t sub_rows = (rows % step) ? rows / step + 1 : rows / step;
        std::size_t sub_cols = (cols % step) ? cols / step + 1 : cols / step;

        std::vector<std::vector<std::pair<float, int>>> submatrices;
        for(int i = 0; i < sub_rows; ++i) {
            submatrices.emplace_back(std::vector<std::pair<float, int>>(sub_cols));
        }


        for(std::size_t i = 0; i < rows; ++i) {
            for(std::size_t j = 0; j < cols; ++j) {
                std::size_t row = i / step;
                std::size_t col = j / step;
                submatrices[row][col].first += matrix[i][j];
                ++submatrices[row][col].second;
            }
        }


        std::vector<std::vector<float>> averages;
        for(std::size_t i = 0; i < sub_rows; ++i) {
            averages.emplace_back(std::vector<float>(sub_cols));
            for(std::size_t j = 0; j < sub_cols; ++j) {
                averages[i][j] = submatrices[i][j].first / submatrices[i][j].second;
            }
        }


        std::ofstream result;
        result.open("result.txt", std::ios::trunc);

        if(result.is_open()) {
            for(std::size_t i = 0; i < sub_rows; ++i) {
                for(std::size_t j = 0; j < sub_cols; ++j) {
                    result << std::fixed << std::setprecision(2) << averages[i][j] << '\t';
                }
                result << '\n';
            }

            std::cout << "see \"result.txt\" for the result.";
            result.close();
        }

        file.close();
    }

    std::cin.get();
    return 0;
}