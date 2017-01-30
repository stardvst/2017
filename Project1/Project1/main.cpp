#include <iostream>


template<typename T>
class Vector {
public:

  class iterator {
  public:
    iterator(T* address) :element(address) {}
    T& operator*() { return *element; }
    void operator++() { ++element; }
    bool operator==(const iterator& x) const { return x.element == element; }
    bool operator!=(const iterator& x) const { return x.element != element; }
  private:
    T* element;
  };

  explicit Vector(int init_size = 0) 
    :the_size(init_size), the_capacity(init_size + SPARE_CAPACITY) {
    arr = new T[the_capacity];
  }
  Vector(const Vector& rhs) 
    :arr(0) { 
    operator=(rhs); 
  }
  ~Vector() {
    delete[] arr;
  }

  const Vector& operator=(const Vector& rhs) {
    if(this != &rhs) {
      delete[] arr;
      the_size = rhs.size();
      the_capacity = rhs.the_capacity;

      arr = new T[the_size];
      for(int k = 0; k < the_size; ++k) {
        arr[k] = rhs.arr[k];
      }
    }
    return *this;
  }

  void resize(int new_size) {
    if(new_size > the_capacity) {
      reserve(new_size * 2 + 1);
    }
    the_size = new_size;
  }

  void reserve(int new_capacity) {
    if(new_capacity < the_size) {
      return;
    }

    T* old = arr;
    arr = new T[new_capacity];
    for(int k = 0; k < the_size; ++k) {
      arr[k] = old[k];
    }

    the_capacity = new_capacity;
    delete[] old;
  }

  T& operator[](int index) { 
    if(index < 0 || index >= the_size) { throw std::exception(); }
    return arr[index]; 
  }
  const T& operator[](int index) const { 
    if(index < 0 || index >= the_size) { throw std::exception(); }
    return arr[index]; 
  }

  bool empty() const { return size() == 0; }
  int size() const { return the_size; }
  int capacity() const { return the_capacity; }

  void push_back(const T& x) {
    if(the_size == the_capacity) {
      reserve(2 * the_capacity + 1);
    }
    arr[the_size++] = x;
  }

  void pop_back() const { --the_size; }
  const T& back() const { return arr[the_size - 1]; }


  //typedef T* iterator;
  //typedef const T* const_iterator;

  iterator begin() { return iterator(&arr[0]); }
  //const_iterator begin() const { return &arr[0]; }
  iterator end() { return iterator(&arr[size()]); }
  //const_iterator end() const { return &arr[size()]; }

  enum { SPARE_CAPACITY = 16 };


  /* 3.8 */
  void insert(T* position, const T& x) {
    if(the_size == the_capacity) {
      reserve(2 * the_capacity + 1);
    }

    if(position == &arr[the_size - 1]) {
      push_back(x);
    } else {
      T* old = arr;
      arr = new T[the_size + 1];

      int i = 0;
      for(T* it = old; it != position; ++it, ++i) {
        arr[i] = old[i];
      }
      arr[i] = x;
      for(; i < the_size; ++i) {
        arr[i + 1] = old[i];
      }

      delete[] old;
      ++the_size;
    }
  }

  void erase(T* position) {
    T* old = arr;
    arr = new T[the_size - 1];

    int i = 0;
    int j = 0;
    for(T* it = old; it != &old[the_size]; ++it, ++j) {
      if(it != position) {
        arr[i++] = old[j];
      }
    }

    delete[] old;
    --the_size;
  }

  /* 3.10 */
  void insert(iterator position, const T& x) {
    if(the_size == the_capacity) {
      reserve(2 * the_capacity + 1);
    }

    if(position == iterator(&arr[the_size - 1])) {
      push_back(x);
    } else {
      T* old = arr;
      arr = new T[the_size + 1];

      int i = 0;
      for(iterator it = iterator(old); it != position; ++it, ++i) {
        arr[i] = old[i];
      }
      arr[i] = x;
      for(; i < the_size; ++i) {
        arr[i + 1] = old[i];
      }

      delete[] old;
      ++the_size;
    }
  }

private:
  int the_size;
  int the_capacity;
  T* arr;
};

int main() {
  
  Vector<int> vi(10);
  for(int i = 0; i < 10; ++i) {
    vi[i] = 0;
  }
 
  vi.insert(vi.begin(), 4);
  vi.insert(&vi[4], 7);
  vi.insert(&vi[7], 8);
  vi[2] = 2;
  for(Vector<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\nsize: " << vi.size() << "\n\n";

  vi.erase(&vi[0]);
  vi.erase(&vi[1]);
  vi.erase(&vi[2]);
  vi.erase(&vi[3]);
  vi.erase(&vi[4]);
  vi.erase(&vi[5]);
  vi.erase(&vi[6]);

  vi.erase(&vi[5]);
  vi.erase(&vi[4]);
  vi.erase(&vi[3]);
  vi.erase(&vi[2]);
  vi.erase(&vi[1]);
  vi.erase(&vi[0]);
  std::cout << "erased, size: " << vi.size() << "\n";
  for(int i = 0; i < vi.size(); ++i) { // prints nothing
    std::cout << vi[i] << " ";
  }

  /* 3.9 */
  /*
    a call to push_back, pop_back, insert, erase invalidates
    all iterators because:
    1. insert and erase allocate new arrays
    2. push_back allocates new array if needed
    3. The call to pop_back() removes the last element in the 
    vector and so the iterator to that element is invalidated. 
    The pop_back() call does not invalidate iterators to items 
    before the last element, only reallocation will do that
  */

  std::cin.get();
  return 0;
}