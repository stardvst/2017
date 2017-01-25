#include <iostream>

template<typename T>
class List {
private:
  struct Node {
    T data;
    bool deleted;
    Node* prev;
    Node* next;

    Node(T d = T(), bool del = 0, Node* p = 0, Node* n = 0) 
      :data(d), deleted(del), prev(p), next(n) {}
  };

public:
  class const_iterator {
    friend class List<T>;
  public:
    const_iterator() {}
    const T& operator*() const { return retrieve(); }

    const_iterator& operator++() { current = current->next; return *this; }
    const_iterator operator++(int) { const_iterator old = *this; ++(*this); return old; }
    const_iterator& operator--() { current = current->prev; return *this; }
    const_iterator operator--(int) { const_iterator old = *this; --(*this); return old; }

    /*const_iterator operator+(int k) const {
      if(k > the_list->size()) { throw std::exception(); }
      const_iterator ret_val = *this;
      for(size_t i = 0; i < k; ++i) {
        if(ret_val.current->next == 0) { throw std::exception(); }
        ++ret_val;
      }
      return ret_val;
    }*/
    const_iterator operator+(int k) const {
      const_iterator ret_val(*the_list, current);
      for(size_t i = 0; i < k; ++i) {
        if(ret_val.current->next == 0) { throw std::exception(); }
        ++ret_val;
      }
      return ret_val;
    } 

    bool operator==(const const_iterator& rhs) const { return current == rhs.current; }
    bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }
  protected:
    const List<T>* the_list;
    Node* current;

    const_iterator(const List<T>& lst, Node* p) :the_list(&lst), current(p) {}
    void assert_is_valid() const {
      if(the_list == 0 || current == 0 || current == the_list->head) {
        throw std::exception();
      }
    }

    T& retrieve() const { if(!current->deleted) { return current->data; } }
  };

  class const_reverse_iterator :public const_iterator {
    friend class List<T>;
  public:
    const_reverse_iterator() {}
    const T& operator*() const { return const_iterator::retrieve(); }
    
    const_reverse_iterator& operator++() { current = current->prev; return *this; }
    const_reverse_iterator operator++(int) { const_reverse_iterator old = *this; --(*this); return old; }
    const_reverse_iterator& operator--() { current = current->next; return *this; }
    const_reverse_iterator operator--(int) { const_reverse_iterator old = *this; ++(*this); return old; }

    const_iterator operator+(int k) const {
      if(k > the_list->size()) { throw std::exception(); }
      const_iterator ret_val = *this;
      for(size_t i = 0; i < k; ++i) {
        if(ret_val.current->prev == 0) { throw std::exception(); }
        --ret_val;
      }
      return ret_val;
    }
  protected:
    const_reverse_iterator(const List<T>& lst, Node* p) :const_iterator(lst, p) {}
  };

  class iterator :public const_iterator {
    friend class List<T>;
  public:
    iterator() {}
    T& operator*() { return retrieve(); }
    const T& operator*() const { return const_iterator::operator*(); }

    iterator& operator++() { current = current->next; return *this; }
    iterator operator++(int) { iterator old = *this; ++(*this); return old; }
    iterator& operator--() { current = current->prev; return *this; }
    iterator operator--(int) { iterator old = *this; --(*this); return old; }
  protected:
    iterator(const List<T>& lst, Node* p) :const_iterator(lst, p) {}
  };

  class reverse_iterator :public const_reverse_iterator {
    friend class List<T>;
  public:
    reverse_iterator() {}
    T& operator*() { return retrieve(); }
    const T& operator*() const { return const_reverse_iterator::operator*(); }

    reverse_iterator& operator++() { return const_iterator::operator--(); }
    reverse_iterator operator++(int) { reverse_iterator old = *this; --(*this); return old; }
    reverse_iterator& operator--() { return iterator::operator++(); }
    reverse_iterator operator--(int) { reverse_iterator old = *this; ++(*this); return old; }

    reverse_iterator operator+(int k) const {
      if(k > the_list->size()) { throw std::exception(); }
      reverse_iterator ret_val = *this;
      for(size_t i = 0; i < k; ++i) {
        if(ret_val.current->prev == 0) { throw std::exception(); }
        --ret_val;
      }
      return ret_val;
    }
  protected:
    reverse_iterator(const List<T>& lst, Node* p) :const_reverse_iterator(lst, p) {}
  };

public:
  List() { init(); }
  List(const List& rhs) { init(); *this = rhs; }
  ~List() { clear(); delete head; delete tail; }
  const List& operator=(const List& rhs) {
    if(this != &rhs) {
      clear();
      for(const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr) {
        push_back(*itr);
      }
    }
    return *this;
  }

  iterator begin() { return iterator(*this, head->next); }
  reverse_iterator rbegin() { return reverse_iterator(*this, tail->prev); }
  const_iterator begin() const { return const_iterator(*this, head->next); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(*this, tail->prev); }
  iterator end() { return iterator(*this, tail); }
  reverse_iterator rend() { return reverse_iterator(*this, head); }
  const_iterator end() const { return const_iterator(*this, tail); }
  const_reverse_iterator rend() const { return const_reverse_iterator(*this, head); }

  int size() const { return the_size; }
  bool empty() const { return the_size == 0; }

  void clear() {
    while(!empty()) {
      pop_front();
    }
  }

  T& front() { return *begin(); }
  const T& front() const { return *begin(); }
  T& back() { return *end(); }
  const T& back() const { return *end(); }

  void push_front(const T& o) { insert(begin(), o); }
  void push_back(const T& o) { insert(end(), o); }
  void pop_front() { erase(begin()); }
  void pop_back() { erase(--end()); }

  iterator insert(iterator itr, const T& o) {
    itr.assert_is_valid();
    if(itr.the_list != this) {
      throw std::exception();
    }

    Node* p = itr.current;
    ++the_size;
    ++nondeleted;
    return iterator(*this, p->prev = p->prev->next = new Node(o, 0, p->prev, p));
  }

  //iterator erase(iterator& itr) {
  //  itr.assert_is_valid();
  //  if(itr.the_list != this) { throw std::exception(); }

  //  Node* p = itr.current;
  //  iterator ret_val(*this, p->next);
  //  if(deleted == nondeleted) {
  //    for(const_iterator it = begin(); it != end(); ++it) {
  //      if(it.current->deleted) { delete p; }
  //    }
  //    the_size -= deleted;
  //    //itr = iterator();
  //  } else {
  //    if(p->next) { p->next->prev = p->prev; }
  //    p->prev->next = p->next; 
  //    p->deleted = 1;
  //  }
  //  return ret_val;
  //}

  iterator erase(iterator itr) {
    itr.assert_is_valid();
    if(itr.the_list != this) {
      throw std::exception();
    }

    Node* p = itr.current;
    iterator ret_val(*this, p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    //itr.current = 0;
    itr = iterator(); /* 3.18 */
    --the_size;

    return ret_val;
  }
  iterator erase(iterator start, iterator end) {
    start.assert_is_valid();
    end.assert_is_valid();
    if(start.the_list != this || end.the_list != this) {
      throw std::exception();
    }
     
    for(iterator itr = start; itr != end; ) {
      itr = erase(itr);
    }
    return end;
  }

  void splice(iterator position, List<T>& lst) {
    position.assert_is_valid();
    if(position.the_list != this) {
      throw std::exception();
    }

    if(this != &lst) {
      iterator& l1it = position;
      iterator l2it = lst.begin();
      while(l2it != lst.end()) {
        insert(l1it, *l2it);
        ++l2it;
      }
    }
    //lst.erase(lst.begin(), lst.end());
  }
  //void splice(iterator position, List<T>& lst) {
  //  if(this != &lst) {
  //    Node* tmp = position.current;
  //    iterator it = lst.begin();
  //    position.current->next = it.current;
  //    position.current->next->prev = position.current;
  //    (lst.end()).current->next = tmp->next;
  //    tmp->next->prev = (lst.end()).current->next;
  //  }
  //  //lst.erase(lst.begin(), lst.end());
  //}

private:
  size_t the_size;
  Node* head;
  Node* tail;
  size_t deleted;
  size_t nondeleted;

  void init() {
    the_size = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    head->deleted = 0;
    tail->prev = head;
    tail->deleted = 0;
    deleted = 0;
    nondeleted = 0;
  }
};


int main() {
  
  List<int> l;
  List<int> d;

  l.push_front(5);
  l.push_back(7);
  l.insert(l.begin(), 8);

  try {
    l.insert(d.begin(), 4);
  }
  catch(const std::exception&) {
    std::cerr << "can't insert to another list\n\n";
  }

  std::cout << "head -> ";
  for(List<int>::const_iterator itr = l.begin(); itr != l.end(); ++itr) {
    std::cout << *itr << " -> ";
  }
  std::cout << "tail\n";

  /* 3.13 .*/
  std::cout << "tail -> ";
  for(List<int>::const_iterator itr = l.end(); itr != l.begin();) {
    --itr;
    std::cout << *itr << " -> ";
  }
  std::cout << "head\n\n";

  /* 3.14 */
  List<int>::const_iterator cit = l.begin();
  try {
    std::cout << *(cit + 2) << "\n\n";
  }
  catch(const std::exception&) {
    std::cerr << "can't advance iterator to that\n\n";
  }

  /* 3.15 */
  List<int> ll;
  ll.push_back(10);
  ll.push_back(11);
  List<int>::iterator it = l.begin();
  ++it;
  l.splice(it, ll);
  std::cout << "head -> ";
  for(List<int>::const_iterator itr = l.begin(); itr != l.end(); ++itr) {
    std::cout << *itr << " -> ";
  }
  std::cout << "tail\n";

  /* 3.16 */
  std::cout << "tail -> ";
  List<int>::const_reverse_iterator rit = l.rbegin();
  while(rit != l.rend()) {
    std::cout << *rit << " -> ";
    ++rit;
  };
  std::cout << "head\n";

  /* 3.18 */
  l.erase(l.begin());
  //std::cout << *(l.begin());

  /* 3.20 */
  std::cout << "head -> ";
  for(List<int>::const_iterator itr = l.begin(); itr != l.end(); ++itr) {
    std::cout << *itr << " -> ";
  }
  std::cout << "tail\n";
 

  std::cin.get();
  return 0;
}