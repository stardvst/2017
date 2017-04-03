#include <iostream>


int main() {

  int w = 0;
  char a[10][10];
  char* s = "Hello world bye earth";

  for(int i = 0; i < strlen(s); ++i) {
    if(s[i] == ' ') {
      int k = 0;
      for(int j = i; j < strlen(s); ++j) {
        if(s[j] != ' ') {
          a[w][k] = s[j];
          k++;
          a[w][k] = '\0';
          i++;
        } else {
          break;
        }
      }
    } else {
      continue;
    }
    w++;
  }

  std::cin.get();
  return 0;
}