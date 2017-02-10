#include <iostream>
#include <string>


void reverse(std::string&, int, int);

void reverse_words(std::string& line) {
  reverse(line, 0, line.length() - 1);

  int word_start = 0;
  for(int i = 0; i < line.length(); ++i) {
    if(line[i] == ' ') {
      reverse(line, word_start, i - 1);
      word_start = i + 1;
    } else if(i == line.length() - 1) {
      reverse(line, word_start, i);
    }
  }
}

void reverse(std::string& word, int start, int end) {
  while(start < end) {
    std::swap(word[start], word[end]);
    ++start;
    --end;
  }
}

int main() {

  std::string line = "she is nice";
  reverse_words(line);
  std::cout << line;

  std::cin.get();
}