#ifndef STACK_HPP
#define STACK_HPP


template<typename T>
class Stack {
public:
  virtual ~Stack() {}
  virtual void push(const T&) = 0;
  virtual void pop() = 0;
  virtual T& top() = 0;
  virtual bool empty() const = 0;
  virtual size_t size() const = 0;
};


#endif // !STACK_HPP
