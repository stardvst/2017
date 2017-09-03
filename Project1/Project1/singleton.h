#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <vector>

class singleton {
public:
    static singleton *get_instance() {
        if(!m_instance) { // lazy init (don't init until 1st use)
            m_instance = new singleton();
        }
        return m_instance;
    }

    void print() const {
        for(int i = 0; i < 10; ++i) {
            std::cout << m_vector[i] << ' ';
        }
        std::cout << std::endl;
    }

protected:
    singleton() {
        for(int i = 0; i < 10; ++i) {
            m_vector.push_back(i);
        }
    }

private:
    static singleton *m_instance;

private:
    std::vector<int> m_vector;
};

bool operator==(const singleton &s1, const singleton &s2) {
    return s1.get_instance() == s2.get_instance();
}

#endif // !SINGLETON_H
