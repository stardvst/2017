#include <vector>

struct B {
    virtual ~B() = default; // plus the other default operations
    virtual std::vector<int> get_vec() const = 0;
};

template<typename T>
struct D : B {
    std::vector<int> get_vec() const override { return m_v; }
    std::vector<int> m_v;
};

// BETTER!
struct B {
    virtual ~B() = default; // plus the other default operations
    virtual std::vector<int> get_vec() const { return m_v; }
    std::vector<int> m_v;
};

template<typename T>
struct D : B {};
