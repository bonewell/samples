#include <iostream>
#include <future>

using namespace std;

int pow(int i)
{
    cout << "thread: " << this_thread::get_id() << endl;
    this_thread::sleep_for(5s);
    return i * i;
}

int main()
{
    cout << "thread: " << this_thread::get_id() << endl;
    packaged_task<int(int)> tsk(pow);
    auto f = tsk.get_future();
    tsk(3);
    cout << "output = " << f.get() << endl;

    tsk.reset();
    f = tsk.get_future();
    async(move(tsk), 7);
    auto o = f.get();
    cout << "output = " << o << endl;
    return 0;
}

