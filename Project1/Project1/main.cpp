#include <iostream>
#include <cstdio>
#include <string>

struct ExecuteInterface {
    virtual ~ExecuteInterface() {}
    virtual void execute() = 0;
};

template<typename T>
struct ExecuteAdapter : ExecuteInterface {
    ExecuteAdapter(T *o, void(T:: *m)()) : object(o), method(m) {}
    ~ExecuteAdapter() { delete object; }
    void execute() override { (object->*method)(); }
private:
    T *object;
    void(T:: *method)();
};

struct Fea {
    ~Fea() { std::cout << "Fea::dtor\n"; }
    void do_this() { std::cout << "Fea::do_this()\n"; }
};

struct Feye {
    ~Feye() { std::cout << "Feye::dtor\n"; }
    void do_that() { std::cout << "Feye::do_that()\n"; }
};

struct Pheau {
    ~Pheau() { std::cout << "Pheau::dtor\n"; }
    void do_other() { std::cout << "Pheau::do_this()\n"; }
};

ExecuteInterface **init() {
    ExecuteInterface **arr = new ExecuteInterface *[3];
    arr[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::do_this);
    arr[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::do_that);
    arr[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::do_other);
    return arr;
}

int main() {

    ExecuteInterface **obs = init();
    for(int i = 0; i < 3; ++i)
        obs[i]->execute();

    for(int i = 0; i < 3; ++i)
        delete obs[i];

    delete obs;

    std::cin.get();
    return 0;
}
