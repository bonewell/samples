#include <iostream>
#include <sstream>
#include <numeric>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
    using bytes = vector<unsigned char>;
    bytes mac = {0x12, 0x23, 0x34, 0x45, 0x56, 0x0f};

    auto mac_ss = accumulate(next(begin(mac)), end(mac),
        stringstream{} << hex << setfill('0') << int{mac.front()},
        [] (auto& ss, int b) {
            return move(ss) << ':' << setw(2) << b;
        });

    cout << mac_ss.str() << '\n';
    return 0;
}
