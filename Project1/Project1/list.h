#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <cstddef>

#include "node.h"

template<typename T>
class List {
public:

    class Iterator {
        template<typename T>
        friend bool operator==(const typename Iterator &it1, const typename Iterator &it2);
        template<typename T>
        friend bool operator!=(const typename Iterator &it1, const typename Iterator &it2);

        friend class List;
    public:
        Iterator(Node<T> *const node);
        
        T& operator*();
        typename Iterator& operator++();

        bool operator==(const typename Iterator &it);
        bool operator!=(const typename Iterator &it);
    private:
        Node<T> *m_node;
        static Node<T> *m_base;
    };

    List();
    ~List();

    T& front();
    const T& front() const;
    Iterator begin() const;

    T& back();
    const T& back() const;
    Iterator end() const;

    void push_front(const T &value);
    void push_back(const T &value);
    void pop_front();
    void pop_back();

    bool erase(const T &value); // returns false if no node was found (and deleted)

    std::size_t size() const;
    bool empty() const;

    void insert(typename Iterator iterator, const T &value);

    void clear();

private:
    Node<T> *m_head; // dummy node
    Node<T> *m_tail;
    std::size_t m_size;

private:
    List(const List &list);
};

/**
    List::Iterator class implementation 
*/
template<typename T>
List<T>::Iterator::Iterator(Node<T> *const node) : m_node(node) {}

template<typename T>
T& List<T>::Iterator::operator*() {
    return m_node->value;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    m_node = m_node->next;
    return *this;
}

template<typename T>
bool List<T>::Iterator::operator==(const typename List<T>::Iterator &it) {
    return m_node == it.m_node;
}

template<typename T>
bool List<T>::Iterator::operator!=(const typename List<T>::Iterator &it) {
    return !(*this == it);
}

/**
    List::Iterator class helper functions
*/
template<typename T>
bool operator==(const typename List<T>::Iterator &it1, const typename List<T>::Iterator &it2) {
    return it1.operator==(it2);
}

template<typename T>
bool operator!=(const typename List<T>::Iterator &it1, const typename List<T>::Iterator &it2) {
    return !(it1 == it2);
}

/** 
    List class implementation 
*/
template<typename T>
List<T>::List() : m_head(new Node<T>), m_tail(m_head), m_size(0) {}

template<typename T>
List<T>::~List() {
    clear();
    delete m_head;

    if(m_head != m_tail) {
        delete m_tail;
    }
}

template<typename T>
T& List<T>::front() {
    assert(!empty());
    return m_head->next->value;
}

template<typename T>
const T& List<T>::front() const {
    assert(!empty());
    return m_head->next->value;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(m_head->next);
}

template<typename T>
T& List<T>::back() {
    assert(!empty());
    return m_tail->value;
}

template<typename T>
const T& List<T>::back() const {
    assert(!empty());
    return m_tail->value;
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr);
}

template<typename T>
void List<T>::push_front(const T &value) {
    m_head->next = new Node<T>(value, m_head->next);

    if(empty()) { // if the list is empty
        m_tail = m_head->next; // make the tail pointer point to the new node 
    }

    ++m_size;
}

template<typename T>
void List<T>::push_back(const T &value) {
    m_tail->next = new Node<T>(value);
    m_tail = m_tail->next; // the element was appended, so update the tail pointer
    ++m_size;
}

template<typename T>
void List<T>::pop_front() {
    assert(!empty());

    Node<T> *tmp = m_head->next;
    m_head->next = tmp->next; // m_head->next = m_head->next->next
    
    if(size() == 1) { // if it was the only element in the list
        m_tail = m_head->next; // make head and tail point to the dummy node
    }

    --m_size;
}

template<typename T>
void List<T>::pop_back() {
    assert(!empty());

    // since we're going to delete the tail,
    // find the node before tail which will become the new tail
    Node<T> *tmp = m_head;
    while(tmp->next != m_tail) {
        tmp = tmp->next;
    }

    delete m_tail; // delete the current tail

    // update the tail
    m_tail = tmp;
    m_tail->next = nullptr;

    --m_size;
}

template<typename T>
bool List<T>::erase(const T &value) {
    assert(!empty());

    // we'll keep two pointers: one for the current node and one for the previous one 
    Node<T> *prev = m_head;
    for(Node<T> *tmp = m_head->next; tmp; /* move both pointers forward */ prev = tmp, tmp = tmp->next) {
        if(tmp->value == value) {
            prev->next = tmp->next;

            if(tmp == m_tail) { // if we're deleting the last element, we need to update the tail
                m_tail = prev;
            }

            delete tmp;
            --m_size;

            return true;
        }
    }

    return false; // if we reach this point, no node with given value was found
}

template<typename T>
std::size_t List<T>::size() const {
    return m_size;
}

template<typename T>
bool List<T>::empty() const {
    return size() == 0;
}

template<typename T>
void List<T>::insert(typename List<T>::Iterator it, const T &value) {
    Node<T> *tmp = m_head;
    while(tmp->next != it.m_node) {
        tmp = tmp->next;
    }

    tmp->next = new Node<T>(value, it.m_node);
}

template<typename T>
void List<T>::clear() {
    // run over the list and delete every node except head (the dummy node)
    while(m_head->next) {
        Node<T> *tmp = m_head->next;
        m_head->next = tmp->next;
        delete tmp;
    }

    m_tail = m_head; // make head and tail point to the dummy node
    m_size = 0; // set list size 0
}

#endif // !LIST_H
