#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <random>

using namespace std;

queue<char> recvq;
condition_variable recv_cond;
mutex recv_mutex;

queue<char> sendq;
condition_variable send_cond;
mutex send_mutex;

void producer() {
    default_random_engine eng;
    
    uniform_int<char> chardist {'a', 'z'};
    while(true) {
        char c = chardist(eng);
        
        unique_lock<mutex> recv_lock { recv_mutex };
        recvq.push(c);
        recv_cond.notify_one(); // notify modifier
        recv_lock.unlock(); // unlock explicitly

        this_thread::sleep_for(chrono::milliseconds(100)); 
    }
}

void modifier() {
    while(true) {
        unique_lock<mutex> recv_lock { recv_mutex };
        
        while(recvq.empty())
            recv_cond.wait(recv_lock); // wait for a notif from producer
        
        char c = recvq.front();
        recvq.pop(); // the modification we need the lock for
        recv_lock.unlock();
        
        c -= 32; // to uppercase
        
        unique_lock<mutex> send_lock { send_mutex };
        sendq.push(c);
        send_cond.notify_one();
        // not calling unlock
    } // send_lock is released
}

void consumer() {
    while(true) {
        unique_lock<mutex> send_lock { send_mutex };
        
        while(sendq.empty())
            send_cond.wait(send_lock); // wait for a notif from modifier

        char c = sendq.front();
        sendq.pop();
        cout << c << endl;
    } // send_lock is released
}

int main() {

    thread t1 { producer };
    thread t2 { modifier };
    thread t3 { consumer };

    t1.join();
    t2.join();
    t3.join();

    std::cin.get();
    return 0;
}
