#ifndef NODE_HPP
#define NODE_HPP


template<typename T>
struct Node {
    T value;
    Node* parent;
    Node* left;
    Node* right;
    char color;

    Node(const T& v) : value(v), parent(0), left(0), right(0), color('r') {}
};

#endif // !NODE_HPP
