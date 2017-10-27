#include <iostream>

struct Widget {
    virtual void draw() = 0;
};

struct TextField : Widget {
    TextField(int w, int h) : width(w), height(h) {}
    void draw() { std::cout << "TextField: " << width << ", " << height << '\n'; }
private:
    int width, height;
};

struct Decorator : Widget {
    Decorator(Widget *wid) : w(wid) {}
    void draw() { w->draw(); }
private:
    Widget *w;
};

struct BorderDecorator : Decorator {
    BorderDecorator(Widget *w) : Decorator(w) {}
    void draw() {
        Decorator::draw();
        std::cout << "   BorderDecorator\n";
    }
};

struct ScrollDecorator : Decorator {
    ScrollDecorator(Widget *w) : Decorator(w) {}
    void draw() {
        Decorator::draw();
        std::cout << "   ScrollDecorator\n";
    }
};

int main() {

    Widget *w = new BorderDecorator(
        new BorderDecorator(
            new ScrollDecorator(
                new TextField(80, 24)
            )
        )
    );

    w->draw();

    std::cin.get();
    return 0;
}
