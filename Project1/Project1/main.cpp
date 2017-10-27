#include <iostream>
#include <vector>

struct Component {
    virtual void traverse() = 0;
};

struct Leaf : Component {
    Leaf(int val) : v(val) {}
    void traverse() { std::cout << v << ' '; }
private:
    int v;
};

struct Composite : Component {
    void add(Component *c) { children.push_back(c); }
    void traverse() {
        for(std::size_t i = 0; i < children.size(); ++i) {
            children[i]->traverse();
        }
    }
private:
    std::vector<Component *> children;
};

int main() {

    Composite containers[4];
    
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 3; ++j) {
            containers[i].add(new Leaf(i * 3 + j));
        }
    }

    for(int i = 1; i < 4; ++i) {
        containers[0].add(&containers[i]);
    }

    for(int i = 0; i < 4; ++i) {
        containers[i].traverse();
        std::cout << '\n';
    }

    std::cin.get();
    return 0;
}
