#ifndef LIST_HPP
#define LIST_HPP


template <typename T>
class List {
public:
  List() {}
  virtual ~List() {}

  virtual bool insert(const T&) = 0;
  virtual bool append(const T&) = 0;
  
  virtual bool erase(const T&) = 0;
  virtual bool erase_curr() = 0;
  virtual bool clear() = 0;
  
  virtual void move_to_start() = 0;
  virtual void move_to(int) = 0;
  virtual bool next() = 0;
  
  virtual int curr_pos() const = 0;
  virtual T get_value() const = 0;
  virtual bool empty() const = 0;
  virtual size_t get_size() const = 0;
private:
  List(const List&) {}
  const List& operator=(const List&) {}
};

#endif // !LIST_HPP