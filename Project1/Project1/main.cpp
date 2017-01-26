#include <iostream>

/* 3.2(a) - swap two adjacent elements */
template<typename T>
class singly_linked_list {
public:
  singly_linked_list() : head(0), size(0) {}

  void insert(int value) {
    Node* newNode = new Node(value);
    if(!head) { 
      head = newNode; 
    } else {
      Node* tmp = head;
      while(tmp->next) {
        tmp = tmp->next;
      }
      tmp->next = newNode;
    }
    ++size;
  }

  void swap_adjacent() {
    if(size == 0 || size == 1) { return; }

    Node* prev = 0;
    Node* current = head;
    Node* next = current->next;

    head = next;

    while(current != 0 && next != 0) {
      current->next = next->next;
      next->next = current;
      
      if(prev != 0) {
        prev->next = next;
      }

      prev = current;
      current = current->next;

      if(current != 0) {
        next = current->next;
      }
    }
  }

  void print() const {
    Node* tmp = head;
    for(size_t i = 1; i <= size; ++i) {
      std::cout << tmp->data << ' ';
      tmp = tmp->next;
    }
  }
private:
  struct Node {
    T data;
    Node* next;

    Node(T d = T(), Node* n = 0) :data(d), next(n) {}
  };

private:
  Node* head;
  size_t size;
};


int main() {

  singly_linked_list<int> slli;

  slli.insert(4);
  slli.insert(6);
  slli.insert(7);
  slli.insert(9);
  slli.insert(5);
  slli.insert(1);

  slli.print();

  std::cout << '\n';
  slli.swap_adjacent();
  slli.print();

  std::cin.get();
  return 0;
}