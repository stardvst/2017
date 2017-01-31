#include <iostream>

template<typename T>
class singly_linked_list {
  template<typename U>
  friend class Methods;
public:
  singly_linked_list() : head(0) {}

private:
  struct Node {
    T data;
    Node* next;

    Node(T d = T(), Node* n = 0) :data(d), next(n) {}
  };

private:
  Node* head;
};

template<typename T>
class Methods {
public:
  int size(const singly_linked_list<T>& lst) const {
    typename singly_linked_list<T>::Node* tmp = lst.head;
    int size = 0;
    while(tmp) {
      ++size;
      tmp = tmp->next;
    }
    return size;
  }

  void print(const singly_linked_list<T>& lst) const {
    typename singly_linked_list<T>::Node* tmp = lst.head;
    while(tmp) {
      std::cout << tmp->data << ' ';
      tmp = tmp->next;
    }
  }

  bool contains(const singly_linked_list<T>& lst, T value) const {
    typename singly_linked_list<T>::Node* tmp = lst.head;
    while(tmp) {
      if(tmp->data == value) {
        return true;
      }
      tmp = tmp->next;
    }
    return false;
  }

  void add(singly_linked_list<T>& lst, T value) {
    if(!contains(lst, value)) {
      typename singly_linked_list<T>::Node* newNode = new singly_linked_list<T>::Node(value);
      if(!lst.head) {
        lst.head = newNode;
      } else {
        singly_linked_list<T>::Node* tmp = lst.head;
        while(tmp->next) {
          tmp = tmp->next;
        }
        tmp->next = newNode;
      }
    }
  }

  void remove(singly_linked_list<T>& lst, T value) {
    typename singly_linked_list<T>::Node* tmp = lst.head;
    typename singly_linked_list<T>::Node* prev = 0;
    while(tmp) {
      if(tmp->data == value) {
        if(tmp == lst.head) {
          lst.head = tmp->next;
          delete tmp;
        } else {
          prev->next = tmp->next;
          delete tmp;
          tmp = prev->next;
        }
      } else {
        prev = tmp;
        tmp = tmp->next;
      }
    }
  }

  void sort(singly_linked_list<T>& lst) {
    for(typename singly_linked_list<T>::Node* index = lst.head; index != 0; index = index->next) {
      for(typename singly_linked_list<T>::Node* selection = index->next;
          selection != 0; selection = selection->next) {
        if(selection->data > index->data) {
          T tmp = index->data;
          index->data = selection->data;
          selection->data = tmp;
        }
      }
    }
  }

  /* 3.12 */
  // a. size  - the same
  // b. print - the same

  bool contains_sorted(const singly_linked_list<T>& lst, T value) const {
    typename singly_linked_list<T>::Node* tmp = lst.head;
    while(tmp && tmp->data >= value) {
      if(tmp->data == value) {
        return true;
      }
      tmp = tmp->next;
    }
    return false;
  }

  void add_sorted(singly_linked_list<T>& lst, T value) {
    if(!contains(lst, value)) {
      typename singly_linked_list<T>::Node* newNode = new singly_linked_list<T>::Node(value);
      if(!lst.head) {
        lst.head = newNode;
      } else {
        singly_linked_list<T>::Node* tmp = lst.head;
        while(tmp && tmp->data >= value) {
          if(!tmp->next || (tmp->next && tmp->next->data < value)) { // !tmp->next - inserting as last item
            newNode->next = tmp->next;
            tmp->next = newNode;
            return;
          }
          tmp = tmp->next;
        }
      }
    }
  }

  void remove_sorted(singly_linked_list<T>& lst, T value) {
    typename singly_linked_list<T>::Node* tmp = lst.head;
    typename singly_linked_list<T>::Node* prev = 0;
    while(tmp && tmp->data >= value) {
      if(tmp->data == value) {
        if(tmp == lst.head) {
          lst.head = tmp->next;
          delete tmp;
        } else {
          prev->next = tmp->next;
          delete tmp;
          tmp = prev->next;
        }
      } else {
        prev = tmp;
        tmp = tmp->next;
      }
    }
  }

};

int main() {

  singly_linked_list<int> slli;
  Methods<int> methods;

  methods.add(slli, 4);
  methods.add(slli, 6);
  methods.add(slli, 7);
  methods.add(slli, 9);
  methods.add(slli, 1);
  methods.add(slli, 5);

  methods.print(slli);
  std::cout << "\nsize: " << methods.size(slli);
  std::cout << "\nlist contains 5: " << std::boolalpha << methods.contains(slli, 5);
  std::cout << "\nlist contains 3: " << std::boolalpha << methods.contains(slli, 3);
  
  methods.add(slli, 3);
  std::cout << "\nadded 3 to the list: ";
  methods.print(slli);

  methods.remove(slli, 3);
  std::cout << "\nremoved 3 from the list: ";
  methods.print(slli);

  methods.sort(slli);
  std::cout << "\n\nsorted list: ";
  methods.print(slli);

  std::cout << "\nsorted list contains 5: " << std::boolalpha << methods.contains_sorted(slli, 5);
  std::cout << "\nsorted list contains 3: " << std::boolalpha << methods.contains_sorted(slli, 3);

  methods.add_sorted(slli, 0);
  std::cout << "\nadded 0 to the sorted list: ";
  methods.print(slli);

  methods.remove_sorted(slli, 0);
  std::cout << "\nremoved 0 from the list: ";
  methods.print(slli);

  std::cin.get();
  return 0;
}