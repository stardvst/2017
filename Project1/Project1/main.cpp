#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>


int main() {

  std::ifstream infile;
  infile.open("words.txt");

  if(infile.is_open()) {
    std::map<std::string, std::set<int> > words;

    std::string row;
    int max_columns = 0;
    while(std::getline(infile, row)) {
      
      int column = 0;
      std::string word;
      std::istringstream line(row);
      while(line >> word) {
        words[word].insert(column++);
      }

      if(column > max_columns) {
        max_columns = column;
      }

    }

    for(std::map<std::string, std::set<int> >::const_iterator it = words.begin();
        it != words.end(); ++it) {
      if(it->second.size() == max_columns) { // word appears in all columns
        std::cout << it->first << '\n';
      }
    }

    infile.close();
  }


  std::cin.get();
  return 0;
}
