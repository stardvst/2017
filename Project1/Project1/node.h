#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node {
    T value;
    Node *next;

    Node(const T &v = T(), Node *const n = nullptr) : value(v), next(n) {}
};

#endif // !NODE_H
