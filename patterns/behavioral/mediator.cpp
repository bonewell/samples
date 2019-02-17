#include <iostream>
#include <thread>
#include <chrono>

class Person {};
enum class Event { started, finished, terminated };
std::ostream& operator<<(std::ostream& out, Event event) {
    switch(event) {
        case Event::started: return out << "started";
        case Event::finished: return out << "finished";
        case Event::terminated: return out << "terminated";
    }
}

class Mediator {
public:
    virtual void notify(Person* sender, Event event) = 0;
    virtual ~Mediator() = default;
};

class Developer : public Person {
public:
    Developer(Mediator& m): m_{m} {}
    void start() { m_.notify(this, Event::started); }
    void stop() { m_.notify(this, Event::finished); }
private:
    Mediator& m_;
};

class Tester : public Person {
public:
    Tester(Mediator& m): m_{m} {}
    void testing() {
        m_.notify(this, Event::started);
    }
    void terminate() {
        m_.notify(this, Event::terminated);
    }
private:
    Mediator& m_;
};

class Manager : public Mediator {
public:
    void notify(Person* sender, Event event) override {
        if (sender == dev_) {
            std::cout << "Developer " << event << "\n";
            if (event == Event::finished) test_->testing();
        }
        if (sender == test_) {
            std::cout << "Tester " << event << "\n";
            if (event == Event::terminated) dev_->start();
        }
    }
    void bind(Developer& d, Tester& t) {
        dev_ = &d;
        test_ = &t;
    }
private:
    Developer* dev_;
    Tester* test_;
};

int main() {
    Manager m;
    Developer d{m};
    Tester t{m};
    m.bind(d, t);

    d.start();
    d.stop();
    std::this_thread::sleep_for(std::chrono::seconds{1});
    t.terminate();
}
