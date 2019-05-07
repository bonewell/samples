#include <iostream>
#include <queue>

class Invokable {
    public:
        virtual void execute() = 0;
        virtual ~Invokable() = default;
};

template<typename T>
class Command: public Invokable {
    public:
        Command(T value): value_{value}{}
        void execute() override {
            std::cout << "Command: " << value_ << "\n";
        }
    private:
        T value_;
};

template<typename T>
using Request = std::function<T()>;

template<typename T>
class Query: public Invokable {
    public:
        Query(Request<T> func):
            result_{}, func_{func} {}
        void execute() override {
            result_ = func_();
        }
        T get() {
            return result_;
        }
    private:
        T result_;
        Request<T> func_;
};

int main() {
    std::queue<Invokable*> invokables;
    Command c1{1};
    invokables.push(&c1);
    Query<int> q1{[]() { return 3; }};
    invokables.push(&q1);
    Command c2{3.5};
    invokables.push(&c2);
    Query<double> q2{[]() { return 7.4; }};
    invokables.push(&q2);
    Command c3{"Hi!"};
    invokables.push(&c3);

    while (!invokables.empty()) {
        invokables.front()->execute();
        invokables.pop();
    }

    std::cout << q1.get() << "\n";
    std::cout << q2.get() << "\n";
}