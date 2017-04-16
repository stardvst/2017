#include <iostream>
#include <thread>


void f_thr() {
  std::cout << "welcome to multithreading!\n";
}

void print_values(int i, char* c, double d) {
  std::cout << i << ' ' << c << ' ' << d << std::endl;
}

class A {
public:
  void operator()() {
    std::cout << "operator()\n";
  }
  void other_function() {
    std::cout << "other function";
  }
};

class B {
public:
  void operator()(int* arr, int size) {
    std::cout << "an array of size " << size << " is passed to thread.\n";
    for(int i = 0; i != size; ++i) {
      std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
  }
  void func_with_params(int* arr, int size) {
    std::cout << "an array of size " << size << " is passed to thread.\n";
    for(int i = 0; i != size; ++i) {
      std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << "Changing sign of all elements of initial array\n";
    for(int i = 0; i != size; ++i) {
      arr[i] *= -1;
      std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
  }
};

int main() {

  // std::thread t(f_thr); // welcome to multithreading!

  // A a;
  // std::thread t(a); // operator()
  // std::thread t(&A::other_function, a); // other function

  // char* str = "Hello world!";
  // std::thread t(print_values, 10, str, 2.5);

  // B b;
  // int arr[6] = { 1,2,3,4,5,6 };
  // std::thread t(b, arr, 6);
  // std::thread t(&B::func_with_params, b, arr, 6);

  std::thread t1(f_thr);
  std::thread t2(f_thr);
  std::thread t3(f_thr);

  std::thread::id id1 = t1.get_id();
  std::thread::id id2 = t2.get_id();
  std::thread::id id3 = t3.get_id();

  if(t1.joinable()) {
    t1.join();
    std::cout << "Thread with id " << id1 << " is terminated" << std::endl;
  }
  if(t2.joinable()) {
    t2.join();
    std::cout << "Thread with id " << id2 << " is terminated" << std::endl;
  }
  if(t3.joinable()) {
    t3.join();
    std::cout << "Thread with id " << id3 << " is terminated" << std::endl;
  }


  // t.detach(); // t becomes not joinable => else {} executes
  /*if(t.joinable()) {
    t.join();
  } else {
    std::cout << "t is detached.\n";
  }*/

  std::cin.get();
  return 0;
}
