#include <iostream>
#include <fstream>
#include <string>
#include <set>


int main() {

  std::fstream iofile;
  iofile.open("csv1.txt");

  if(iofile.is_open()) {

    std::set<std::string> lines;

    std::string line;
    std::streampos pos = iofile.tellg();

    while(std::getline(iofile, line)) {
      if(lines.find(line) == lines.end()) {
        lines.insert(line);
      } else {
        std::streampos next = iofile.tellg();
        iofile.seekp(pos);

        std::string tmp = std::string(line.length(), ' ');
        iofile << tmp;

        iofile.seekg(next);
        continue;
      }

      pos = iofile.tellg();
    }

    iofile.close();
  }


  std::cout << "see \"csv1.txt\" for the result.";

  std::cin.get();
  return 0;
}
