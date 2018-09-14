#include <iostream>
#include <memory>

using namespace std;

int main()
{
    shared_ptr<string> ptr1(new string("Hello World!"));
    shared_ptr<string> ptr2 = ptr1;

    cout << ptr1 << endl;
    cout << ptr2 << endl;

    ptr2 = new string("Bye World!"); // Error of build

    cout << ptr1 << endl;
    cout << ptr2 << endl;

    return 0;
}

