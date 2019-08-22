//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>

using namespace std;

// Complete the sumXor function below.
long sumXor(long n) {
    long count = 1;
    long x = 1;
    while (x < n) {
        if ((n & x) == 0) {
            count *= 2;
        }
        x = (x << 1);
    }
    return count;
}


int main()
{
 	cout << sumXor(5) << "\n";
 	cout << sumXor(10) << "\n";

	return 0;
}