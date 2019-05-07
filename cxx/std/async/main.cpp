#include <iostream>
#include <future>

using namespace std;

int iterate(int x, int y)
{
    cout << "Id: " << this_thread::get_id() << endl;
    for(int i{x}; i < y; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(1s);
        this_thread::yield();
    }
    return 5;
}

int main()
{
    cout << "Id: " << this_thread::get_id() << endl;
    auto f = async(iterate, 0, 5);

    cout << f.get() << endl;
    this_thread::sleep_for(10s);

    return 0;
}

