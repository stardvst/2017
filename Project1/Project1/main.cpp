#include <iostream>
#include <vector>

struct AlarmListener {
    virtual void alarm() = 0;
};

struct SensorSystem {
    void attach(AlarmListener *al) { listeners.push_back(al); }
    void soundTheAlarm() {
        for(std::size_t i = 0; i < listeners.size(); ++i) {
            listeners[i]->alarm();
        }
    }
private:
    std::vector<AlarmListener *> listeners;
};

struct Lighting : AlarmListener {
    void alarm() { std::cout << "lights up\n"; }
};

struct Gates : AlarmListener {
    void alarm() { std::cout << "gates close\n"; }
};

struct CheckList {
    void byTheNunbers() {
        localize();
        identify();
        identify();
    }
private:
    virtual void localize() { std::cout << "   establish a perimeter\n"; }
    virtual void isolate() { std::cout << "   isloate the grid\n"; }
    virtual void identify() { std::cout << "   identify the source\n"; }
};

struct Surveillance : CheckList, AlarmListener {
    void alarm() {
        std::cout << "Surveillance - by the numbers:\n";
        byTheNunbers();
    }
private:
    void isolate() {
        std::cout << "   train the cameras\n";
    }
};

int main() {

    SensorSystem ss;
    ss.attach(&Gates());
    ss.attach(&Lighting());
    ss.attach(&Surveillance());
    ss.soundTheAlarm();

    std::cin.get();
    return 0;
}
