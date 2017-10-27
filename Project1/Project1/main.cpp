#include <iostream>

struct TimeImp {
    TimeImp(int h, int m) : m_h(h), m_m(m) {}
    virtual void tell() {
        std::cout << "time is " << m_h << m_m << '\n';
    }
protected:
    int m_h, m_m;
};

struct CivilianTimeImp : TimeImp {
    CivilianTimeImp(int h, int m, int pm) : TimeImp(h, m) {
        if(pm)
            strcpy(m_whichM, " PM");
        else
            strcpy(m_whichM, " AM");
    }
    void tell() {
        std::cout << "time is " << m_h << ":" << m_m << m_whichM << '\n';
    }
protected:
    char m_whichM[4];
};

struct ZuluTimeImp : TimeImp {
    ZuluTimeImp(int h, int m, int zone) : TimeImp(h, m) {
        if(zone == 5)
            strcpy(m_zone, " Eastern Std Time");
        else if(zone == 6)
            strcpy(m_zone, " Central Std Time");
    }
    void tell() {
        std::cout << "time is " << m_h << m_m << m_zone << '\n';
    }
protected:
    char m_zone[30];
};

struct Time {
    Time() {}
    Time(int h, int m) { imp = new TimeImp(h, m); }
    virtual void tell() { imp->tell(); }
protected:
    TimeImp *imp;
};

struct CivilianTime : Time {
    CivilianTime(int h, int m, int pm) { imp = new CivilianTimeImp(h, m, pm); }
};

struct ZuluTime : Time {
    ZuluTime(int h, int m, int zone) { imp = new ZuluTimeImp(h, m, zone); }
};

int main() {

    Time *times[3];
    times[0] = new Time(14, 30);
    times[1] = new CivilianTime(2, 30, 1);
    times[2] = new ZuluTime(14, 30, 6);
    for(int i = 0; i < 3; ++i)
        times[i]->tell();

    std::cin.get();
    return 0;
}
