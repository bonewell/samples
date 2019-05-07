#include <atomic>
#include <vector>
#include <thread>
#include <shared_mutex>  // c++17
#include <memory>
#include <list>
#include <iostream>
#include <iomanip>
#include <memory_resource>  // c++17 (compiler should support this feature)

using namespace std;

pmr::synchronized_pool_resource pool;

struct Message {
    //vector<int> data = vector<int>(128);
    pmr::vector<int> data = pmr::vector<int>(128, &pool);
};

constexpr int kLimit = 100'000;  // ' requires c++14
constexpr int kNumberOfProducers = 16;
constexpr int kNumberOfCustomers = 4;
shared_mutex m;
//list<shared_ptr<Message>> msgs;
pmr::list<shared_ptr<Message>> msgs{ &pool };
atomic<int> stopped = 0;

void write() {
    for (int n = 0; n != kLimit; ++n) {
        lock_guard lk{ m };  // using without template parameter requires c++17
    //    msgs.push_back(make_shared<Message>());
        msgs.push_back(allocate_shared<Message, pmr::polymorphic_allocator<Message>>(&pool));
    }
    ++stopped;
}

void read() {
    int size = 0;
    while (true) {
        {
            shared_lock lk{ m };  // just to show using shared mutex and lock
            size = msgs.size();
        }
        lock_guard lk{ m };
        cout << setw(10) << setfill(' ') << size << "\r";
        if (!msgs.empty()) {
            msgs.pop_front();
        }
        else {
            if (stopped == kNumberOfProducers) break;
        }
    }
}

int main() {
    std::vector<thread> cs(kNumberOfCustomers);
    for (auto& c : cs) {
        c = thread{ read };
        cout << "start customer " << c.get_id() << "\n";
    }

    std::vector<thread> ps(kNumberOfProducers);
    for (auto& p : ps) {
        p = thread{ write };
        cout << "start producer " << p.get_id() << "\n";
    }

    for (auto& p : ps) {
        p.join();
    }

    for (auto& c : cs) {
        c.join();
    }
}