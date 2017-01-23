#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


int main() {

  std::vector<std::vector<char> > board { { 't', 'h', 'i', 's' },
                                          { 'w', 'a', 't', 's' },
                                          { 'o', 'a', 'h', 'g' },
                                          { 'f', 'g', 'o', 't' } };

  std::vector<std::string> words = { "this", "his", "is", "hi", "at", "hat", "go",
                                     "that", "two", "it", "fat", "to", "got", "oh" };

  std::vector<std::string> guessed_words;

  // ->
  for(size_t row = 0; row < board.size(); ++row) {
    for(size_t letter = 0; letter < board.size() - 1; ++letter) {
      std::string word(1, board[row][letter]);
      for(size_t other = letter + 1; other < board.size(); ++other) {
        word.append(1, board[row][other]);
        if(std::find(words.begin(), words.end(), word) != words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }

  // |
  // v
  for(size_t row = 0; row < board.size(); ++row) {
    for(size_t letter = 0; letter < board.size() - 1; ++letter) {
      std::string word(1, board[letter][row]);
      for(size_t other = letter + 1; other < board.size(); ++other) {
        word.append(1, board[other][row]);
        if(std::find(words.begin(), words.end(), word) != words.end() &&
           std::find(guessed_words.begin(), guessed_words.end(), word) == guessed_words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }

  // <-
  for(size_t row = board.size() - 1; row > 0; --row) {
    for(size_t letter = board.size() - 1; letter > 0; --letter) {
      std::string word(1, board[row][letter]);
      for(size_t other = letter - 1; other > 0; --other) {
        word.append(1, board[row][other]);
        if(std::find(words.begin(), words.end(), word) != words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }

  // ^
  // |
  for(size_t row = board.size() - 1; row > 0; --row) {
    for(size_t letter = board.size() - 1; letter > 0; --letter) {
      std::string word(1, board[letter][row]);
      for(size_t other = letter - 1; other > 0; --other) {
        word.append(1, board[other][row]);
        if(std::find(words.begin(), words.end(), word) != words.end() &&
           std::find(guessed_words.begin(), guessed_words.end(), word) == guessed_words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }


  // \
  //  >
  for(size_t row = 0; row < board.size() - 1; ++row) {
    for(size_t col = 0; col < board.size() - 1; ++col) {
      std::string word(1, board[row][col]);

      int new_row = row;
      int new_col = col;

      for(int i = col + 1; i < board.size() - row; ++i) {
        ++new_row;
        ++new_col;
        word.append(1, board[new_row][new_col]);
        if(std::find(words.begin(), words.end(), word) != words.end() &&
           std::find(guessed_words.begin(), guessed_words.end(), word) == guessed_words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }


  //  /
  // <
  for(size_t row = 0; row < board.size() - 2; ++row) {
    for(size_t col = board.size() - 1; col > 0; --col) {
      std::string word(1, board[row][col]);

      int new_row = row;
      int new_col = col;

      for(int i = 0; i < col - row; ++i) {
        ++new_row;
        --new_col;
        word.append(1, board[new_row][new_col]);
        if(std::find(words.begin(), words.end(), word) != words.end() &&
           std::find(guessed_words.begin(), guessed_words.end(), word) == guessed_words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }


  //  ^
  // /
  for(size_t row = board.size() - 1; row > 0; --row) {
    for(size_t col = 0; col < board.size() - 1; ++col) {
      std::string word(1, board[row][col]);

      size_t new_row = row;
      size_t new_col = col;

      for(size_t i = 0; i < abs(static_cast<long>(row - col)); ++i) {
        --new_row;
        ++new_col;
        word.append(1, board[new_row][new_col]);
        if(std::find(words.begin(), words.end(), word) != words.end() &&
           std::find(guessed_words.begin(), guessed_words.end(), word) == guessed_words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }


  // ^
  /*  \ */
  for(size_t row = board.size() - 1; row > 0; --row) {
    for(size_t col = board.size() - 1; col > 0; --col) {
      std::string word(1, board[row][col]);

      size_t new_row = row;
      size_t new_col = col;

      for(size_t i = 0; i < std::min(row, col); ++i) {
        --new_row;
        --new_col;
        word.append(1, board[new_row][new_col]);
        if(std::find(words.begin(), words.end(), word) != words.end() &&
           std::find(guessed_words.begin(), guessed_words.end(), word) == guessed_words.end()) {
          guessed_words.push_back(word);
          std::cout << word << std::endl;
        }
      }
    }
  }

  std::cin.get();
  return 0;
}