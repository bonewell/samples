#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std::chrono;

class Time {
    public:
        static Time& instance() {
            static Time time;
            return time;
        }
        std::string get() {
            auto time = system_clock::to_time_t(system_clock::now());
            return std::string{ctime(&time)};
        }
};

int main() {
    std::cout << Time::instance().get() << "\n";
    std::this_thread::sleep_for(seconds(2));
    std::cout << Time::instance().get() << "\n";
}