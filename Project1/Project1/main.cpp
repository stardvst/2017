#include <iostream>
#include <thread>
#include <mutex>


std::mutex m;

void make_a_call() {
  m.lock();
  std::cout << "Hello my friend, this is " << std::this_thread::get_id() << '\n';
  m.unlock();
}


int main() {

  std::thread person1(make_a_call);
  std::thread person2(make_a_call);
  std::thread person3(make_a_call);

  if(person1.joinable()) {
    person1.join();
  }
  if(person2.joinable()) {
    person2.join();
  }
  if(person3.joinable()) {
    person3.join();
  }

  std::cin.get();
  return 0;
}

