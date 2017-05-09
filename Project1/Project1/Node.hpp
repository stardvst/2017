#ifndef NODE_HPP
#define NODE_HPP


template<typename T>
struct Node {
    Node(const T& v) : value(v), parent(0), left(0), right(0), color('r') {}

    T value;
    Node* parent;
    Node* left;
    Node* right;
    char color;
};

#endif // !NODE_HPP
