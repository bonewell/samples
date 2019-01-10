#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std;
using namespace std::chrono;

class Time {
    public:
        static Time& instance() {
            static Time time;
            return time;
        }
        string get() {
            auto time = system_clock::to_time_t(system_clock::now());
            return string{ctime(&time)};
        }
};

int main() {
    cout << Time::instance().get() << "\n";
    this_thread::sleep_for(seconds(2));
    cout << Time::instance().get() << "\n";
}