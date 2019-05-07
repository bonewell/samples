#include <iostream>
#include <memory>
#include <thread>

using namespace std;

shared_ptr<string> gptr(new string("I'm global"));

void func1(shared_ptr<string> ptr) {
    while (ptr) {
        cout << ptr->c_str() << endl;
        cout << ptr.use_count() << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

// void func2(shared_ptr<string>& ptr) { // compilation error
void func2(shared_ptr<string> ptr) {
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Do reset\n";
    cout << ptr.use_count() << endl;
    ptr.reset();
    cout << ptr.use_count() << endl;
}

int main()
{
    auto* s = new string("Hello World!");
    shared_ptr<string> ptr1(s);
    shared_ptr<string> ptr2 = ptr1;
    //ptr2 = new string("Bye World!"); // Error of build
    shared_ptr<string> ptr3(new string("Bye World!"));
    shared_ptr<string> ptr4(s);

    cout << ptr1 << endl;
    cout << ptr2 << endl;
    cout << ptr3 << endl;


    ptr3 = ptr1;

    cout << ptr1 << endl;
    cout << ptr2 << endl;
    cout << ptr3 << endl;

    ptr2.reset();
    ptr3.reset();

    cout << ptr1.use_count() << endl;
    auto& ptr = ptr1;

    thread a1{func1, ptr1};
    ptr1.reset();
    thread a2{func2, ptr4};
    ptr4.reset();
    a1.join();
    a2.join();

    cout << "End\n";

    return 0;
}

