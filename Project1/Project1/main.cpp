#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>


int main() {

    std::ifstream file;
    file.open("table.txt");

    if(file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        std::string line;
        std::getline(file, line);
        std::stringstream iss(line);

        int index = -1;
        std::unordered_map<std::string, int> columns;
        while(iss >> line) {
            columns[line] = ++index;
        }

        std::getline(file, line); // skip dashes


        std::string pivot_column = "";
        while(columns.find(pivot_column) == columns.end()) {
            std::cout << "pivot: ";
            std::cin >> pivot_column;
        }

        std::string data_column = "";
        while(columns.find(data_column) == columns.end()) {
            std::cout << "data: ";
            std::cin >> data_column;
        }

        std::string other_column = "-";
        while(columns.find(other_column) == columns.end()) {
            std::cout << "column: ";
            std::cin >> other_column;
        }

        int pivot_index = columns[pivot_column];
        int data_index = columns[data_column];
        int column_index = columns[other_column];

        size_t data = 0;
        std::unordered_map<std::string, std::list<std::vector<std::string>>> pivot_table; // pivot - data mapping
        while(std::getline(file, line)) {
            iss.clear();
            iss.str(line);

            std::vector<std::string> current_row;
            while(iss >> line) {
                current_row.push_back(line);
            }

            std::vector<std::string> entry;
            entry.push_back(current_row[data_index]);
            entry.push_back(current_row[column_index]);
            pivot_table[current_row[pivot_index]].push_back(entry);
            ++data;
        }


        std::ofstream result;
        result.open("pivot_table.txt");

        if(result.is_open()) {
            result << std::setw(10) << other_column;

            for(std::unordered_map<std::string, std::list<std::vector<std::string>>>::const_iterator
                it = pivot_table.begin(); it != pivot_table.end(); ++it) {
                result << std::setw(10) << (*it).first;
            }
            result << '\n';
            for(std::size_t i = 0; i <= pivot_table.size(); ++i) {
                result << "-----------";
            }
            result << '\n';


            size_t deleted = 0;
            const size_t size = pivot_table.size();

            while(deleted != data) {
                std::unordered_map<std::string, std::list<std::vector<std::string>>>::iterator
                    it = pivot_table.begin();

                for(; (*it).second.empty(); ++it);
                std::string column = (*it).second.front()[1];
                result << std::setw(10) << column;

                for(it = pivot_table.begin(); it != pivot_table.end(); ++it) {

                    std::list<std::vector<std::string>> list = (*it).second;
                    if(!list.empty()) {
                        int sum = 0;
                        for(std::list<std::vector<std::string>>::iterator it2 = (*it).second.begin();
                            it2 != (*it).second.end(); ) {
                            if((*it2)[1] == column) {
                                sum += std::stoi((*it2)[0]);
                                (*it).second.erase(it2++);
                                ++deleted;
                            } else {
                                ++it2;
                            }
                        }
                        
                        if(sum == 0) {
                            result << std::setw(10) << ' ';
                        } else {
                            result << std::setw(10) << sum;
                        }
                    } else {
                        result << std::setw(10) << ' ';
                    }
                }

                result << '\n';
            }

        }
    }


    return 0;
}
