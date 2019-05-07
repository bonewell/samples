#include <iostream>
#include <future>

using namespace std;

int pow(future<int>& f)
{
    cout << "thread: " << this_thread::get_id() << endl;
    auto v = f.get();
    cout << "input = " << v << endl;
    this_thread::sleep_for(5s);
    return v * v;
}

int main()
{
    cout << "thread: " << this_thread::get_id() << endl;
    promise<int> i;
    auto fi = i.get_future();
    auto fo = async(pow, ref(fi));
    this_thread::sleep_for(5s);
    i.set_value(3);
    auto o = fo.get();
    cout << "output = " << o << endl;
    return 0;
}

