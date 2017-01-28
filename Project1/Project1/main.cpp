#include <iostream>

/* 3.2(b) - swap two adjacent elements */
template<typename T>
class doubly_linked_list {
public:
  doubly_linked_list() : head(0), tail(0) {}

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
  }

  void swap_adjacent() {
    if(head == 0 || head->next == 0) { return; }

    Node* prev = 0;
    Node* current = head;
    Node* next = current->next;

    head = next;

    while(current != 0 && next != 0) {
      current->next = next->next;
      next->next = current;
      next->next->prev = current;

      next->prev = (next != head) ? prev : 0;
      current->prev = next;

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
    while(tmp) {
      std::cout << tmp->data << ' ';
      tmp = tmp->next;
    }
  }
private:
  struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T d = T(), Node* n = 0, Node* p = 0) :data(d), next(n), prev(p) {}
  };

private:
  Node* head;
  Node* tail;
};


int main() {

  doubly_linked_list<int> dlli;

  dlli.insert(4);
  dlli.insert(6);
  dlli.insert(7);
  dlli.insert(9);
  dlli.insert(5);
  dlli.insert(1);

  dlli.print();

  std::cout << '\n';
  dlli.swap_adjacent();
  dlli.print();

  std::cin.get();
  return 0;
}