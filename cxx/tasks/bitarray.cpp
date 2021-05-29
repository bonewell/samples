#include <iostream>

using namespace std;

using byte = uint8_t;
byte calc(byte n, byte s, byte p, byte q)
{
    constexpr byte x{0x7};
    cout << int{s & x} << '\n';
    for (byte i = 1; i < n; ++i)
    {
        s = (s * p + q) & x;
        cout << int{s} << '\n';
    }
    return 10;
}

int main() {
//    byte n, s, p, q;
//    cin >> n >> s >> p >> q;
    byte s;
    cin >> s;
    cout << calc(10, s, 3, 4);

    return 0;
}
