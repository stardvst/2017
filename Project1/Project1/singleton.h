#ifndef SINGLETON_H
#define SINGLETON_H

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

class singleton {
public:
    static void register_singleton(const std::string &name, singleton *const instance) {
        m_registry[name] = instance;
    }

    static singleton *get_instance(const std::string &name) {
        if(!m_instance) {
            m_instance = lookup(name); // returns 0 if no such singleton
        }
        return m_instance;
    }

protected:
    singleton() {}

    static singleton *lookup(const std::string &name) {
        if(m_registry.find(name) == m_registry.end()) {
            return nullptr;
        }
        return m_registry[name];
    }

private:
    static singleton *m_instance;
    static std::unordered_map<std::string, singleton *> m_registry;
};

class singleton_subclass_1 : public singleton {
public:

    static singleton_subclass_1 *get_instance() {
        if(!m_instance) {
            m_instance = new singleton_subclass_1();
        }
        return m_instance;
    }

    void print_until_4() const {
        for(int i = 0; i < 5; ++i) {
            std::cout << m_subclass_vector[i] << ' ';
        }
        std::cout << std::endl;
    }

protected:
    singleton_subclass_1() {
        for(int i = 0; i < 5; ++i) {
            m_subclass_vector.push_back(i);
        }

        singleton::register_singleton("singleton_subclass_1", this);
    }

private:
    static singleton_subclass_1 *m_instance;

private:
    std::vector<int> m_subclass_vector;
};

class singleton_subclass_2 : public singleton {
public:
    static singleton_subclass_2 *get_instance() {
        if(!m_instance) {
            m_instance = new singleton_subclass_2();
        }
        return m_instance;
    }

    void print_until_9() const {
        for(int i = 0; i < 10; ++i) {
            std::cout << m_subclass_vector[i] << ' ';
        }
        std::cout << std::endl;
    }

protected:
    singleton_subclass_2() {
        for(int i = 0; i < 10; ++i) {
            m_subclass_vector.push_back(i);
        }

        singleton::register_singleton("singleton_subclass_2", this);
    }

private:
    static singleton_subclass_2 *m_instance;

private:
    std::vector<int> m_subclass_vector;
};

#endif // !SINGLETON_H
