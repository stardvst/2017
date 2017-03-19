#ifndef AQUEUE_HPP
#define AQUEUE_HPP

#include <cassert>
#include "Queue.hpp"


template<typename T>
class AQueue : public Queue<T> {
public:
  AQueue(size_t n) : max_size(n + 1), queue(new T[max_size]),
    _front(1), rear(0) {}
  ~AQueue() { delete[] queue; }

  void enqueue(const T&);
  void dequeue();
  T front() const;

  size_t size() const;
  bool empty() const;
  bool full() const;

private:
  size_t max_size;
  T* queue;
  mutable int _front;
  int rear;
};


template<typename T>
void AQueue<T>::enqueue(const T& x) {
  assert((rear + 2) % max_size != _front);
  rear = (rear + 1) % max_size;
  queue[rear] = x;
}

template<typename T>
void AQueue<T>::dequeue() {
  assert(!empty());
  _front = (_front + 1) % max_size;
}

template<typename T>
T AQueue<T>::front() const {
  assert(!empty());
  return queue[_front];
}

template<typename T>
size_t AQueue<T>::size() const {
  return ((max_size - _front) + rear + 1) % max_size;
}

template<typename T>
bool AQueue<T>::empty() const {
  return size() == 0;
}

template<typename T>
bool AQueue<T>::full() const {
  return size() == max_size - 1;
}


#endif // !AQUEUE_HPP
