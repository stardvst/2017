#ifndef QUEUE_HPP
#define QUEUE_HPP


template<typename T>
class Queue {
public:
  virtual ~Queue() {}

  virtual void enqueue(const T&) = 0;
  virtual void dequeue() = 0;
  virtual T front() const = 0;

  virtual size_t size() const = 0;
  virtual bool empty() const = 0;
  virtual bool full() const = 0;
};


#endif // !QUEUE_HPP
