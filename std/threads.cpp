// C++17 is used
#include <atomic>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;
using namespace std::placeholders;

class JoiningThread {
public:
    template<typename F, typename... Args>
    explicit JoiningThread(F&& f, Args&&... args):
        t_{forward<F>(f), forward<Args>(args)...}
    {
    }

    ~JoiningThread()
    {
        cout << "~JoiningThread\n";
        if (t_.joinable()) {
            cout << "join\n";
            t_.join();
        }
    }

private:
    thread t_;
};

class DelayedThread {
public:
    template<typename F, typename... Args>
    explicit DelayedThread(F&& f, Args&&... args):
        t_{
            [self = this](auto&& f, auto&&... args)
            {
                if (self->p_.get_future().get())
                    invoke(forward<decltype(f)>(f),
                                forward<decltype(args)>(args)...); 
            },
            forward<F>(f), 
            forward<Args>(args)...
        }
    {
    }

    ~DelayedThread()
    {
        lock_guard _{m_};
        cout << "~DelayedThread\n";
        if (!started_)
            p_.set_value(false);
    }
    
    void start()
    {
        lock_guard _{m_};
        cout << "start\n";
        p_.set_value(started_ = true);
    }

private:
    promise<bool> p_;
    bool started_{false};
    mutex m_;
    JoiningThread t_;    
};

class LoopableThread {
public:
    template<typename F, typename... Args>
    LoopableThread(F&& f, Args&&... args):
        t_{
            [self = this](auto&& f, auto&&... args)
            {
                while (!self->stopped_) {
                    invoke(forward<decltype(f)>(f),
                                forward<decltype(args)>(args)...); 
                }
            },
            forward<F>(f),
            forward<Args>(args)...
        }
    {
    }
    
    ~LoopableThread()
    {
        cout << "~LoopableThread\n";
        stop();
    }

    void start()
    {
        t_.start();
    }

    void stop()
    {
        cout << "stop\n";
        stopped_ = true;
    }

private:
    atomic_bool stopped_{false};
    DelayedThread t_;
};

int main() try {
  using namespace std::chrono;
  {
     JoiningThread jt{
        [](seconds x)
        {
            this_thread::sleep_for(x);
        },
        1s
     };
  }
  {
     DelayedThread dt{[](int x) { cout << x << "\n"; }, 5};
     this_thread::sleep_for(1s);
//      throw "";
     dt.start();
  }

  queue<int> q{deque<int>{1, 2, 3, 4, 5}};

  LoopableThread lt{
      [](auto&& q) 
      {
        if (!q.empty()) {
            const auto x = q.front();
            cout << x << "\n";
            q.pop();
            this_thread::sleep_for(1s);
        }
      },
      q};
  this_thread::sleep_for(1s);
  lt.start();
  this_thread::sleep_for(2s);
//   throw "";
  lt.stop();
} catch (...) {
}