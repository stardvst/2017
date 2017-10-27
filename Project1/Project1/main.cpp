#include <iostream>
#include <cstdio>
#include <string>

// desired interface
struct Rectangle {
    virtual void draw() = 0;
};

// legacy component
struct LegacyRect {
    LegacyRect(int x1, int y1, int x2, int y2) : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {
        std::cout << "LegacyRect: create - ("
            << m_x1 << ", " << m_y1 << ") => (" << m_x2 << ", " << m_y2 << ")\n";
    }
    void old_draw() {
        std::cout << "LegacyRect: old draw - ("
            << m_x1 << ", " << m_y1 << ") => (" << m_x2 << ", " << m_y2 << ")\n";
    }
private:
    int m_x1, m_y1, m_x2, m_y2;
};

// adapter wrapper
struct RectAdapter : Rectangle, private LegacyRect {
    RectAdapter(int x, int y, int w, int h) : LegacyRect(x, y, x + w, y + h) {
        std::cout << "RectAdapter: create - ("
            << x << ", " << y << "), width = " << w << ", height = " << h << "\n";
    }
    virtual void draw() override {
        std::cout << "RectAdapter: draw - \n";
        old_draw();
    }
};

int main() {

    Rectangle *r = new RectAdapter(120, 200, 60, 40);
    r->draw();

    std::cin.get();
    return 0;
}
