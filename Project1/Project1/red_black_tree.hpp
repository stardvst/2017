#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <cassert>
#include <cstring>
#include <stack>
#include <queue>
#include "Node.hpp"


template<typename T>
class RedBlackTree {
    template<typename U>
    friend void preorder(const RedBlackTree<U>&);
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(const T&);
    void remove(const T&);
    bool find(const T&) const;

    const T& minimum() const;
    const T& maximum() const;

    void inorder() const;

    bool empty() const;
private:
    void insert_fixup(Node<T>*&);
    void remove_fixup(Node<T>*&);
private:
    void left_rotate(Node<T>*&);
    void right_rotate(Node<T>*&);
    void transplant(Node<T>*, Node<T>*);

    Node<T>* predecessor(Node<T>*) const;
    Node<T>* successor(Node<T>*) const;

    Node<T>* get_min_node(Node<T>*) const;
    Node<T>* get_max_node(Node<T>*) const;

    Node<T>* find_node(const T&) const;
private:
    Node<T>* nil;
    Node<T>* root;
};


template<typename T>
RedBlackTree<T>::RedBlackTree() : nil(new Node<T>()), root(nil) {
    nil->color = 'b';
    root->parent = nil;
    root->left = nil;
    root->right = nil;
}

template<typename T>
RedBlackTree<T>::~RedBlackTree() {
    if(!empty()) {
        std::queue<Node<T>*> queue;
        queue.push(root);

        while(!queue.empty()) {
            Node<T>* node = queue.front();
            queue.pop();

            if(node->left != nil) {
                queue.push(node->left);
            }
            if(node->right != nil) {
                queue.push(node->right);
            }
            delete node;
        }
    }

    delete nil;
}

template<typename T>
void RedBlackTree<T>::insert(const T& value) {

    Node<T>* y = nil;
    Node<T>* x = root;

    while(x != nil) {
        y = x;
        if(value <= x->value) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    Node<T>* node = new Node<T>(value);
    node->parent = y;

    if(y == nil) {
        root = node;
    } else if(value <= y->value) {
        y->left = node;
    } else {
        y->right = node;
    }

    node->left = nil;
    node->right = nil;

    insert_fixup(node);
}

template<typename T>
void RedBlackTree<T>::insert_fixup(Node<T>*& node) {
    Node<T>* y = 0;

    while(node->parent->color == 'r') {
        if(node->parent == node->parent->parent->left) {
            y = node->parent->parent->right;
            if(y->color == 'r') {
                node->parent->color = 'b';
                y->color = 'b';
                node->parent->parent->color = 'r';
                node = node->parent->parent;
            } else {
                if(node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                node = node->parent->parent;
                right_rotate(node);
            }
        } else {
            y = node->parent->parent->left;
            if(y->color == 'r') {
                node->parent->color = 'b';
                y->color = 'b';
                node->parent->parent->color = 'r';
                node = node->parent->parent;
            } else {
                if(node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                left_rotate(node->parent->parent);
            }
        }
    }

    root->color = 'b';
}


template<typename T>
void RedBlackTree<T>::remove(const T& value) {
    Node<T>* node = find_node(value);

    if(!node) {
        return;
    }

    Node<T>* y = node;
    char y_original_color = node->color;

    Node<T>* x;
    if(node->left == nil) {
        x = node->right;
        transplant(node, node->right);
    } else if(node->right == nil) {
        x = node->left;
        transplant(node, node->left);
    } else {
        y = predecessor(node);
        y_original_color = y->color;
        x = y->left;
        if(y->parent == node) {
            x->parent = y;
        } else {
            transplant(y, y->left);
            y->left = node->left;
            y->left->parent = y;
        }
        transplant(node, y);
        y->right = node->right;
        y->right->parent = y;
        y->color = node->color;
    }

    if(y_original_color == 'b') {
        remove_fixup(x);
    }

    delete node;
}

template<typename T>
void RedBlackTree<T>::remove_fixup(Node<T>*& node) {
    while(node != root && node->color == 'b') {

        Node<T>* sibling;
        if(node == node->parent->left) {
            sibling = node->parent->right;

            if(sibling->color == 'r') { // case 1
                sibling->color = 'b';
                node->parent->color = 'r';
                left_rotate(node->parent);
                sibling = node->parent->right;
            }

            if(sibling->left->color == 'b' && sibling->right->color == 'b') { // case 2
                sibling->color = 'r';
                node = node->parent;
            } else {
                if(sibling->right->color == 'b') { // case 3
                    sibling->left->color = 'b';
                    sibling->color = 'r';
                    right_rotate(sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color; // case 4
                node->parent->color = 'b';
                sibling->right->color = 'b';
                left_rotate(node->parent);
                node = root;
            }
        } else {
            sibling = node->parent->left;

            if(sibling->color == 'r') { // case 1
                sibling->color = 'b';
                node->parent->color = 'r';
                right_rotate(node->parent);
                sibling = node->parent->left;
            }

            if(sibling->left->color == 'b' && sibling->right->color == 'b') { // case 2
                sibling->color = 'r';
                node = node->parent;
            } else {
                if(sibling->left->color == 'b') { // case 3
                    sibling->right->color = 'b';
                    sibling->color = 'r';
                    left_rotate(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color; // case 4
                node->parent->color = 'b';
                sibling->left->color = 'b';
                right_rotate(node->parent);
                node = root;
            }
        }
    }

    node->color = 'b';
}


template<typename T>
bool RedBlackTree<T>::find(const T& value) const {
    Node<T>* tmp = root;
    while(tmp) {
        if(value < tmp->value) {
            tmp = tmp->left;
        } else if(value > tmp->value) {
            tmp = tmp->right;
        } else {
            return true;
        }
    }
    return false;
}

template<typename T>
const T& RedBlackTree<T>::maximum() const {
    assert(!empty());
    Node<T>* tmp = root;
    while(tmp->right) {
        tmp = tmp->right;
    }
    return tmp->value;
}

template<typename T>
const T& RedBlackTree<T>::minimum() const {
    assert(!empty());
    Node<T>* tmp = root;
    while(tmp->left) {
        tmp = tmp->left;
    }
    return tmp->value;
}

template<typename T>
void RedBlackTree<T>::inorder() const {
    assert(!empty());
    std::stack<Node<T>*> stack;

    Node<T>* node = root;
    while(node != nil || !stack.empty()) {
        while(node != nil) {
            stack.push(node);
            node = node->left;
        }
        node = stack.top();
        stack.pop();
        std::cout << node->value << ' ';
        node = node->right;
    }
}

template<typename T>
bool RedBlackTree<T>::empty() const {
    return root->left == nil && root->right == nil;
}

template<typename T>
void RedBlackTree<T>::left_rotate(Node<T>*& node) {
    Node<T>* y = node->right;
    node->right = y->left;
    if(y->left != nil) {
        y->left->parent = node;
    }
    Node<T>* tmp = node;
    y->parent = node->parent;
    if(tmp->parent == nil) {
        root = y;
    } else if(tmp == tmp->parent->left) {
        tmp->parent->left = y;
    } else {
        tmp->parent->right = y;
    }
    y->left = tmp;
    tmp->parent = y;
}

template<typename T>
void RedBlackTree<T>::right_rotate(Node<T>*& node) {
    Node<T>* y = node->left;
    node->left = y->right;
    if(y->right != nil) {
        y->right->parent = node;
    }
    Node<T>* tmp = node;
    y->parent = node->parent;
    if(tmp->parent == nil) {
        root = y;
    } else if(tmp == tmp->parent->left) {
        tmp->parent->left = y;
    } else {
        tmp->parent->right = y;
    }
    y->right = tmp;
    tmp->parent = y;
}

template<typename T>
void RedBlackTree<T>::transplant(Node<T>* node1, Node<T>* node2) {
    if(node1->parent == nil) {
        root = node2;
    } else if(node1 == node1->parent->left) {
        node1->parent->left = node2;
    } else {
        node1->parent->right = node2;
    }
    node2->parent = node1->parent;
}

template<typename T>
Node<T>* RedBlackTree<T>::predecessor(Node<T>* node) const {
    if(node->left != nil) {
        return get_max_node(node->left);
    }
    Node<T>* y = node->parent;
    while(y != nil && node == y->left) {
        node = y;
        y = y->parent;
    }
    return y;
}

template<typename T>
Node<T>* RedBlackTree<T>::successor(Node<T>* node) const {
    if(node->right != nil) {
        return get_min_node(node->right);
    }
    Node<T>* y = node;
    while(y != nil && node == y->right) {
        node = y;
        y = y->parent;
    }
    return y;
}


template<typename T>
Node<T>* RedBlackTree<T>::get_min_node(Node<T>* node) const {
    while(node->left != nil) {
        node = node->left;
    }
    return node;
}

template<typename T>
Node<T>* RedBlackTree<T>::get_max_node(Node<T>* node) const {
    while(node->right != nil) {
        node = node->right;
    }
    return node;
}

template<typename T>
Node<T>* RedBlackTree<T>::find_node(const T& value) const {
    Node<T>* tmp = root;
    while(tmp != nil) {
        if(value < tmp->value) {
            tmp = tmp->left;
        } else if(value > tmp->value) {
            tmp = tmp->right;
        } else {
            return tmp;
        }
    }
    return 0;
}


template<typename U>
void preorder(const RedBlackTree<U>& rbt) {
    std::stack<Node<U>*> stack;
    stack.push(rbt.root);
    Node<U>* nil = rbt.nil;
    while(!stack.empty()) {
        Node<U>* node = stack.top();
        stack.pop();
        std::cout << node->value << ' ';
        if(node->left != nil || node->right != nil) {
            std::cout << "{ ";
        } else if(node == node->parent->right) {
            std::cout << "} ";
        }

        if(node->right != nil) {
            stack.push(node->right);
        }
        if(node->left != nil) {
            stack.push(node->left);
        }
    }
    std::cout << "}";
}

#endif // !RED_BLACK_TREE_HPP
