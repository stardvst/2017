#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <set>


int main() {

  std::fstream iofile;
  iofile.open("csv.txt");

  if(iofile.is_open()) {

    std::set<std::string> lines;
    std::string line;

    std::ofstream copy;
    copy.open("copy.txt");

    if(copy.is_open()) {

      while(std::getline(iofile, line)) {
        if(lines.find(line) == lines.end()) {
          lines.insert(line);
          copy << line << '\n';
        }
      }

      iofile.close();
      copy.close();

      std::remove("csv.txt");
      std::rename("copy.txt", "csv.txt");
    }

  }

  std::cout << "see \"csv.txt\" for the result.";

  std::cin.get();
  return 0;
}
