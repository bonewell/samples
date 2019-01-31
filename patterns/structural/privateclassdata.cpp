#include <iostream>
#include <chrono>
#include <thread>

using Kg = int;
using Metter = int;
using Kmh = double;
using kN = int;

struct TrainData {
    Kg weight;
    Metter length;
    Kmh speed;
    kN force;
};

class Train {
    public:
        Train(Kg weight, Metter length):
            data_{} {
            data_.weight = weight;
            data_.length = length;
        }
        Kmh speed() const {
            if (data_.force == 0) {
                return data_.speed;
            }
            auto current = std::chrono::steady_clock::now();
            auto d = std::chrono::duration_cast<std::chrono::seconds>(current - timestamp);
            double acceleration = double(data_.force * 1000) / data_.weight;
            return data_.speed + (acceleration * d.count() * 3.6);
        }
        void force(kN force) {
            data_.force = force;
            timestamp = std::chrono::steady_clock::now();
        }
    private:
        TrainData data_;
        std::chrono::steady_clock::time_point timestamp;
};

int main() {
    Train t{3000, 1500};
    std::cout << "v0 = " << t.speed() << "\n";
    t.force(5);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "v = " << t.speed() << "\n";
}