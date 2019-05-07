#include <iostream>
#include <memory>
#include <string>

class Elevator;

class State {
public:
    explicit State(Elevator& elevator) : elevator_{elevator} {}
    virtual std::string run() = 0;
    virtual std::string stop() = 0;
    virtual std::string repair() = 0;
    virtual ~State() = default;

protected:
    Elevator& elevator_;
};

class Elevator {
public:
    void changeState(std::unique_ptr<State> state) {
        state_ = std::move(state);
    }
    void run() {
        std::cout << state_->run() << "\n";
    }
    void stop() {
        std::cout << state_->stop() << "\n";
    }
    void repair() {
        std::cout << state_->repair() << "\n";
    }
private:
    std::unique_ptr<State> state_;
};

class Running : public State {
public:
    using State::State;
    std::string run() override {
        return "Already running...";
    }
    std::string stop() override;
    std::string repair() override {
        return "Not stopped.";
    }
};

class Repair : public State {
public:
    using State::State;
    std::string run() override {
        elevator_.changeState(std::make_unique<Running>(elevator_));
        return "Running...";
    }
    std::string stop() override {
        return "Not running!";
    }
    std::string repair() override {
        return "Already repairing...";
    }
};

class Idle : public State {
public:
    using State::State;
    std::string run() override {
        elevator_.changeState(std::make_unique<Running>(elevator_));
        return "Running...";
    }
    std::string stop() override {
        return "Not running!";
    }
    std::string repair() override {
        elevator_.changeState(std::make_unique<Repair>(elevator_));
        return "Repairing...";
    }
};

class Mounted : public State {
public:
    using State::State;
    std::string run() override {
        elevator_.changeState(std::make_unique<Running>(elevator_));
        return "Running...";
    }
    std::string stop() override {
        return "Not running!";
    }
    std::string repair() override {
        return "Not broken!";
    }
};

std::string Running::stop() {
    elevator_.changeState(std::make_unique<Idle>(elevator_));
    return "Stopped.";
}

int main() {
    Elevator e1;
    e1.changeState(std::make_unique<Mounted>(e1));
    e1.run();
    e1.repair();
    e1.stop();
    e1.repair();
}