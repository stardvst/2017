#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <Windows.h>


std::vector<int> vec;
std::mutex mutex;

void push() {
  mutex.lock();
  for(int i = 0; i != 10; ++i) {
    std::cout << "Push " << i << std::endl;
    Sleep(500);
    vec.push_back(i);
  }
  mutex.unlock();
}


void pop() {
  mutex.lock();
  for(int i = 0; i != 10; ++i) {
    if(vec.size() > 0) {
      int val = vec.back();
      vec.pop_back();
      std::cout << "Pop " << val << std::endl;
    }
    Sleep(500);
  }
  mutex.unlock();
}


int main() {

  std::thread push(push);
  std::thread pop(pop);
  if(push.joinable())
    push.join();
  if(pop.joinable())
    pop.join();

  std::cin.get();
  return 0;
}

