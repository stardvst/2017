#include <iostream>

struct burger {
    virtual void desc() = 0;
    virtual int cost() = 0;
};

struct french : burger {
    void desc() { std::cout << "french burger with"; }
    int cost() { return 100; }
};

struct italian : burger {
    void desc() { std::cout << "italian burger with"; }
    int cost() { return 120; }
};

struct decorator : burger {
    decorator(burger *b) : m_burger(b) {}
    void desc() { m_burger->desc(); }
    int cost() { return m_burger->cost(); }
private:
    burger *m_burger;
};

struct cheese : decorator {
    cheese(burger *b) : decorator(b) {}
    void desc() {
        decorator::desc();
        std::cout << " cheese";
    }
    int cost() { return decorator::cost() + 150; }
};

struct sauce : decorator {
    sauce(burger *b) : decorator(b) {}
    void desc() {
        decorator::desc();
        std::cout << " sauce";
    }
    int cost() { return decorator::cost() + 200; }
};

int main() {

    burger *b = new sauce(
        new cheese(
            new french
        )
    );

    b->desc();

    std::cout << "\ncost: " << b->cost() << " dram";
    std::cin.get();
    return 0;
}
