#include <iostream>

struct State;

struct Machine {
    Machine();
    void set_currect(State *);
    void on();
    void off();
private:
    State *current;
};

struct State {
    virtual void on(Machine *) { std::cout << "already ON\n"; }
    virtual void off(Machine *) { std::cout << "already OFF\n"; }
};

void Machine::set_currect(State *s) { current = s; }
void Machine::on() { current->on(this); }
void Machine::off() { current->off(this); }

struct On : State {
    On() { std::cout << "   ON ctor"; }
    ~On() { std::cout << "   ON dtor\n"; }
    void off(Machine *);
};

struct Off : State {
    Off() { std::cout << "   OFF ctor"; }
    ~Off() { std::cout << "   OFF dtor\n"; }
    void on(Machine *);
};

void On::off(Machine *m) {
    std::cout << "  going from ON to OFF";
    m->set_currect(new Off());
    delete this;
}

void Off::on(Machine *m) {
    std::cout << "  going from OFF to ON";
    m->set_currect(new On());
    delete this;
}

Machine::Machine() { current = new Off(); std::cout << '\n'; }

int main() {

    void(Machine:: *ptrs[])() = { &Machine::off, &Machine::on };

    Machine fsm;
    int num;
    while(1) {
        std::cout << "enter 0/1: ";
        std::cin >> num;
        (fsm.*ptrs[num])();
    }

    std::cin.get();
    return 0;
}
