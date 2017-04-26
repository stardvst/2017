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
    while(std::getline(infile, row)) {
      
      int column = 0;
      std::string word;
      std::istringstream line(row);
      while(line >> word) {
        words[word].insert(column++);
      }

    }

    for(std::map<std::string, std::set<int> >::const_iterator it = words.begin();
        it != words.end(); ++it) {
      if(it->second.size() == 1) { // word appears only in 1 column
        std::cout << it->first << '\n';
      }
    }

    infile.close();
  }


  std::cin.get();
  return 0;
}
