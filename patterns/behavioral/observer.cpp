#include <iostream>
#include<vector>

enum class Event { Open, Close };
std::ostream& operator<<(std::ostream& out, Event event) {
    switch (event) {
        case Event::Open: return out << "open";
        case Event::Close: return out << "close";
    }
}

class Observer {
public:
    virtual void updated(Event event) = 0;
    virtual ~Observer() = default;
};

class PostOffice {
public:
    void subscribe(Observer* observer) {
        observers_.push_back(observer);
    }
    void unsubscribe(Observer* observer) {
        auto it = std::find(std::begin(observers_),
            std::end(observers_), observer);
        observers_.erase(it);
    }
    void notify() {
        for (auto o: observers_) {
                o->updated(event_);
        }
    }
    void open() {
        std::cout << "open\n";
        event_ = Event::Open;
        notify();
    }
    void close() {
        std::cout << "close\n";
        event_ = Event::Close;
        notify();
    }
private:
    std::vector<Observer*> observers_;
    Event event_;
};

class Konstantin : public Observer {
public:
    void updated(Event event) override {
        std::cout << "Konstantin: " << event << "\n";
    }
};

class Sofia : public Observer {
    void updated(Event event) override {
        std::cout << "Sofia: " << event << "\n";
    }
};

int main() {
    PostOffice post;
    Konstantin k;
    post.subscribe(&k);
    post.open();

    Sofia s;
    post.subscribe(&s);
    post.unsubscribe(&k);
    post.close();
}