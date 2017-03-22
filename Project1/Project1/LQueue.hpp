#ifndef LQUEUE_HPP
#define LQUEUE_HPP

#include <cassert>
#include "Queue.hpp"


template<typename T>
class LQueue : public Queue<T> {
public:
  LQueue() : m_front(new Node()), m_rear(m_front) {}
  ~LQueue();

  void enqueue(const T&);
  void dequeue();
  T front() const;

  size_t size() const { return m_size; }
  bool empty() const { return size() == 0; }
  bool full() const { return false; }

private:
  struct Node {
    T data;
    Node* next;
    Node(T d = T(), Node* n = 0) : data(d), next(n) {}
  };
private:
  Node* m_front;
  Node* m_rear;
  size_t m_size;
};


template<typename T>
LQueue<T>::~LQueue() {
  while(m_front) {
    Node* tmp = m_front;
    m_front = m_front->next;
    delete tmp;
  }
}

template<typename T>
void LQueue<T>::enqueue(const T& x) {
  m_rear->next = new Node(x);
  m_rear = m_rear->next;
  ++m_size;
}

template<typename T>
void LQueue<T>::dequeue() {
  assert(!empty());
  Node* tmp = m_front->next;
  m_front->next = tmp->next;
  if(m_rear == tmp) {
    m_rear = m_front;
  }
  delete tmp;
  --m_size;
}

template<typename T>
T LQueue<T>::front() const {
  assert(!empty());
  return m_front->next->data;
}


#endif // !LQUEUE_HPP
