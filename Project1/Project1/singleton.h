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

#endif // !SINGLETON_H
