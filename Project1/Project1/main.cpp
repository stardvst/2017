#include <iostream>


template<typename T, int SIZE>
class two_stacks {
public:
  two_stacks() : arr(new T[SIZE]), top1(-1), top2(SIZE) {}

  void push(int stack, const T& x) {
    if(top1 + 1 < top2) {
      switch(stack) {
        case 1: arr[++top1] = x; break;
        case 2: arr[--top2] = x; break;
        default: std::cerr << "oops. non-existent stack\n"; break;
      }
    } else {
      std::cout << "stack overflow\n";
    }
  }

  void pop(int stack) {
    switch(stack) {
      case 1: --top1; break;
      case 2: ++top2; break;
      default: std::cerr << "oops. non-existent stack\n"; break;
    }
  }

  T top(int stack) const {
    switch(stack) {
      case 1: return arr[top1]; break;
      case 2: return arr[top2]; break;
      default: std::cerr << "oops. non-existent stack\n"; break;
    }
  }

  int size(int stack) const { 
    switch(stack) {
      case 1: return top1 + 1; break;
      case 2: return SIZE - top2; break;
      default: std::cerr << "oops. non-existent stack\n"; break;
    }
  }

  bool empty(int stack) const { 
    switch(stack) {
      case 1: return top1 == -1; break;
      case 2: return top2 == SIZE; break;
      default: std::cerr << "oops. non-existent stack\n"; break;
    }
  }

private:
  T* arr;
  int top1;
  int top2;
};


template<typename T, int SIZE>
class three_stacks {
public:
  three_stacks()
    : arr(new T[SIZE]), top1(-1), top2(SIZE), start3(SIZE / 2), end3(SIZE / 2) {}

  void push(int stack, const T& x) {
   switch(stack) {
      case 1:
        if(top1 + 1 < start3) {
          arr[++top1] = x;
        } else if(end3 < top2) {
          int k = SIZE - size(1) - size(2) - size(3); // empty elements number
          if(k == 1) {
            for(int i = end3; i >= start3; --i) {
              arr[i + 1] = arr[i];
            }
          } else {
            for(int i = end3; i >= start3; --i) {
              arr[i + 2 * k / 3] = arr[i];
            }
          }
          arr[++top1] = x;
        } else {
          std::cout << "stack overflow\n";
        }
        break;
      case 2: 
        if(end3 < top2) {
          arr[--top2] = x;
        } else if(top1 + 1 < start3) {
          int k = SIZE - size(1) - size(2) - size(3);
          if(k == 1) {
            for(int i = start3; i <= end3; ++i) {
              arr[i - 1] = arr[i];
            }
            --start3;
            --end3;
          } else {
            for(int i = start3; i <= end3; ++i) {
              arr[i - 2 * k / 3] = arr[i];
            }
            start3 -= 2 * k / 3;
            end3 -= 2 * k / 3;
          }
          arr[--top2] = x;
        } else {
          std::cout << "stack overflow\n";
        }
        break;
      case 3:
        if(size(1) + size(2) + size(3) != SIZE) {
          if(empty(3)) {
            arr[start3] = x;
            end3 = start3 + 1;
          } else if(size(3) % 2 == 1) {
            if(end3 + 1 < top2) {
              arr[end3++] = x;
            } else {
              int k = SIZE - size(1) - size(2) - size(3); // empty elements number
              if(k == 1) {
                for(int i = start3; i <= end3; ++i) {
                  arr[i - 1] = arr[i];
                }
              } else {
                for(int i = start3; i <= end3; ++i) {
                  arr[i - 2 * k / 3] = arr[i];
                }
              }
              arr[end3++] = x;
            }
          } else if(size(3) % 2 == 0) {
            if(top1 + 1 < start3) {
              arr[--start3] = x;
            } else {
              int k = SIZE - size(1) - size(2) - size(3); // empty elements number
              if(k == 1) {
                for(int i = end3 - 1; i >= start3; --i) {
                  arr[i + 1] = arr[i];
                }
              } else {
                for(int i = end3 - 1; i >= start3; --i) {
                  arr[i + 2 * k / 3] = arr[i];
                }
              }
              end3 += 2 * k / 3;
              start3 += 2 * k / 3;
              arr[--start3] = x;
            }
          }
        } else {
          std::cout << "stack overflow\n";
        }
        break;
      default: std::cerr << "oops. non-existent stack " << stack << "\n"; break;
    }
  }

  void pop(int stack) {
    switch(stack) {
      case 1: --top1; break;
      case 2: ++top2; break;
      case 3: size(3) % 2 == 1 ? ++start3 : --end3; break;
      default: std::cerr << "oops. non-existent stack " << stack << "\n"; break;
    }
  }

  T top(int stack) const {
    switch(stack) {
      case 1: return arr[top1]; break;
      case 2: return arr[top2]; break;
      case 3: return size(3) % 2 == 1 ? arr[start3]: arr[end3 - 1]; break;
      default: std::cerr << "oops. non-existent stack " << stack << "\n"; break;
    }
  }

  int size(int stack) const {
    switch(stack) {
      case 1: return top1 + 1; break;
      case 2: return SIZE - top2; break;
      case 3: return end3 - start3; break;
      default: std::cerr << "oops. non-existent stack " << stack << "\n"; break;
     }
  }

  bool empty(int stack) const {
    switch(stack) {
      case 1: return top1 == -1; break;
      case 2: return top2 == SIZE; break;
      case 3: return start3 == end3; break;
      default: std::cerr << "oops. non-existent stack " << stack << "\n"; break;
    }
  }

private:
  T* arr;
  int top1;
  int top2;
  int start3;
  int end3;
};



int main() {
  
  two_stacks<int, 12> stacks12;
  
  /* size, empty */
  std::cout << "stack1 size: " << stacks12.size(1) << '\n'
    << "stack2 size: " << stacks12.size(2) << '\n';

  std::cout << "is stack1 empty?: " << std::boolalpha << stacks12.empty(1) << '\n'
    << "is stack2 empty?: " << std::boolalpha << stacks12.empty(2) << '\n';

  /* push */
  std::cout << "\ninserting elements...\n";
  stacks12.push(1, 5);
  stacks12.push(2, 3);
  stacks12.push(1, 2);
  stacks12.push(1, 4);
  stacks12.push(1, 7);
  stacks12.push(2, 2); 
  stacks12.push(1, 8);
  stacks12.push(2, 9); 
  stacks12.push(3, 6);
  stacks12.push(1, 0);
  stacks12.push(3, 1);
  stacks12.push(3, 4);
  stacks12.push(3, 7); // -
  stacks12.push(2, 8); // -

  std::cout << "\nmaking space in stack1 and inserting...\n";
  stacks12.pop(1);
  stacks12.push(1, 5);

  std::cout << "stack1 size: " << stacks12.size(1) << '\n'
    << "stack2 size: " << stacks12.size(2) << '\n';

  /* top, pop, empty */
  std::cout << "\npopping stack1... ";
  while(!stacks12.empty(1)) {
    std::cout << stacks12.top(1) << ' ';
    stacks12.pop(1);
  }

  std::cout << "\npopping stack2... ";
  while(!stacks12.empty(2)) {
    std::cout << stacks12.top(2) << ' ';
    stacks12.pop(2);
  }

  std::cout << "\n\ninserting into stack3... ";
  stacks12.push(3, 5);




  /* three stacks */
  three_stacks<int, 12> stacks123;

  std::cout << "\n\n--------------------\ntesting stacks123...\n\n";

  /* size, empty */
  std::cout << "stack1 size: " << stacks123.size(1) << '\n'
    << "stack2 size: " << stacks123.size(2) << '\n'
    << "stack3 size: " << stacks123.size(3) << '\n';

  std::cout << "is stack1 empty?: " << std::boolalpha << stacks123.empty(1) << '\n'
    << "is stack2 empty?: " << std::boolalpha << stacks123.empty(2) << '\n'
    << "is stack3 empty?: " << std::boolalpha << stacks123.empty(3) << '\n';

  /* push */
  std::cout << "\ninserting elements...\n";
  stacks123.push(1, 5);
  stacks123.push(1, 3);
  stacks123.push(1, 2);
  stacks123.push(1, 4);
  stacks123.push(1, 1);
  stacks123.push(3, 1);
  stacks123.push(3, 2);
  stacks123.push(3, 8);
  stacks123.push(3, 4);
  stacks123.push(3, 0);
  stacks123.push(2, 1);
  stacks123.push(2, 4);
  stacks123.push(1, 7); // -
  stacks123.push(2, 8); // -

  std::cout << "stack1 size: " << stacks123.size(1) << '\n'
    << "stack2 size: " << stacks123.size(2) << '\n'
    << "stack3 size: " << stacks123.size(3) << '\n';

  /* top, pop, empty */
  std::cout << "\npopping stack1... ";
  while(!stacks123.empty(1)) {
    std::cout << stacks123.top(1) << ' ';
    stacks123.pop(1);
  }

  std::cout << "\npopping stack2... ";
  while(!stacks123.empty(2)) {
    std::cout << stacks123.top(2) << ' ';
    stacks123.pop(2);
  }

  std::cout << "\npopping stack3... ";
  while(!stacks123.empty(3)) {
    std::cout << stacks123.top(3) << ' ';
    stacks123.pop(3);
  }

  std::cout << "\n\ninserting into stack4... ";
  stacks123.push(4, 5);

  std::cin.get();
  return 0;
}
