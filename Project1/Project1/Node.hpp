#ifndef NODE_HPP
#define NODE_HPP


template<typename T>
struct Node {
    T value;
    Node* parent;
    Node* left;
    Node* right;
    char color;
    int size;

    Node(const T& v = T()) : value(v), parent(0), left(0), right(0), color('r'), size(0) {}
};

#endif // !NODE_HPP
