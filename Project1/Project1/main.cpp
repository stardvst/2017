#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <list>
#include <map>


int main() {

  std::ifstream infile("str_matrix.txt");

  std::map<std::string, std::pair<int, std::list<int> > > lines;

  std::string line;
  int index = 0;
  while(std::getline(infile, line)) {
    if(lines.find(line) != lines.end()) {
      ++lines[line].first; // ++frequency
      lines[line].second.push_back(index);
    } else {
      lines[line] = std::make_pair<int, std::list<int> >(1, std::list<int>());
      lines[line].second.push_back(index);
    }
    ++index;
  }


  std::ofstream outfile("unique_m_if.txt", std::ios::trunc);
  outfile
    << std::setw(11) << "word" << std::setw(9) << '|'
    << std::setw(9) << "freq." << std::setw(5) << '|'
    << std::setw(20) << "indexes" << std::setw(12) << '|'
    << "\n------------------------------------------------------------------\n";
  for(std::map<std::string, std::pair<int, std::list<int> > >::const_iterator
      it = lines.begin(); it != lines.end(); ++it) {

    outfile
      << std::setw(11) << it->first
      << std::setw(16) << it->second.first
      << std::setw(14);

    std::list<int>::const_iterator i = it->second.second.begin();
    std::list<int>::const_iterator list_end = --(it->second.second.end());
    for(; i != list_end; ++i) {
      outfile << *i << ", ";
    }
    outfile << *(--(it->second.second.end())) << '\n';
  }


  std::cout << "see \"unique_m_if.txt\" for the result.";

  std::cin.get();
  return 0;
}
