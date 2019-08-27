#include <iostream>
#include <sstream>

using namespace std;

int main () {
    istringstream iss;

    iss.str("abc");
    string str1{"123"};
    getline(iss, str1);
    cout << str1 << '\n';
    
    iss.str("def");
    iss.seekg(0);  // very important
    string str2{"456"};
    getline(iss, str2);
    cout << str2 << '\n';

    return 0;
}
