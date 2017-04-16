#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ctime>
using std::chrono::system_clock;

int main() {

  std::cout << "The id of current thread is " << std::this_thread::get_id() << '\n'; // or get_id

  time_t timet = system_clock::to_time_t(system_clock::now());

  tm* time = localtime(&timet);

  std::cout << "Current time: " << std::put_time(time, "%X") << '\n';
  std::cout << "Waiting for the next minute to begin...\n";

  time->tm_min++;
  time->tm_sec = 0;

  std::this_thread::sleep_until(system_clock::from_time_t(mktime(time)));
  std::cout << std::put_time(time, "%X") << " reached!\n";

  std::this_thread::sleep_for(std::chrono::seconds(5));

  timet = system_clock::to_time_t(system_clock::now());
  time = localtime(&timet);
  std::cout << "Current time: " << std::put_time(time, "%X") << '\n';

  std::cin.get();
  return 0;
}
