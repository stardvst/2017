#include <iostream>
#include <string>

struct car {
    int wheel;
    int power;
    std::string body;
};

struct builder {
    virtual void build_wheel() const = 0;
    virtual void build_power() const = 0;
    virtual void build_body() const = 0;
protected:
    car *m_car;
};

struct x5_builder : builder {
    x5_builder() { m_car = new car; }
    void build_wheel() const override { m_car->wheel = 5; }
    void build_power() const override { m_car->power = 50; }
    void build_body() const override { m_car->body = "bmw x5"; }
    car *get_car() const { return m_car; }
};

struct x6_builder : builder {
    x6_builder() { m_car = new car; }
    void build_wheel() const override { m_car->wheel = 6; }
    void build_power() const override { m_car->power = 60; }
    void build_body() const override { m_car->body = "bmw x6"; }
    car *get_car() const { return m_car; }
};

struct i3_builder : builder {
    i3_builder() { m_car = new car; }
    void build_wheel() const override { m_car->wheel = 3; }
    void build_power() const override { m_car->power = 30; }
    void build_body() const override { m_car->body = "bmw i3"; }
    car *get_car() const { return m_car; }
};

struct director {
    void construct(builder *car_type) {
        car_type->build_wheel();
        car_type->build_power();
        car_type->build_body();
    }
};

int main() {

    const auto d = new director;

    // construct an x5
    const auto x5 = new x5_builder; // construct an x5 builder
    d->construct(x5);               // ask the director to build a car using this builder
    auto c = x5->get_car();         // get the car from the x5 builder

    std::cout
        << "car wheel: " << c->wheel << '\n'
        << "car power: " << c->power << '\n'
        << "car body: " << c->body << "\n\n";


    // construct an x6
    const auto x6 = new x6_builder;
    d->construct(x6);
    c = x6->get_car();

    std::cout
        << "car wheel: " << c->wheel << '\n'
        << "car power: " << c->power << '\n'
        << "car body: " << c->body << "\n\n";

    // construct an i3
    const auto i3 = new i3_builder;
    d->construct(i3);
    c = i3->get_car();

    std::cout
        << "car wheel: " << c->wheel << '\n'
        << "car power: " << c->power << '\n'
        << "car body: " << c->body << "\n\n";

    std::cin.get();
    return 0;
}
