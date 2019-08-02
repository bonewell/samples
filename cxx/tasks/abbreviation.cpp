//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

bool tail(const string& a, int i)
{
    for (int x = i; x < a.length(); ++x) {
        if (isupper(a[x]) != 0) return false;
    }
    return true;
}

unordered_map<int, unordered_map<int, int>> res;

bool compare(const string& a, const string& b, int i = 0, int j = 0)
{
    if (res[i][j] != 0) return (res[i][j] == 1);

    bool r{false};
    if (i >= a.length() && j < b.length()) {
        r = false;
    }
    else if (j >= b.length()) {
        r = tail(a, i);
    }
    else if (a[i] == b[j]) {
        r = compare(a, b, i + 1, j + 1);
    }
    else if (toupper(a[i]) == b[j]) {
        r = compare(a, b, i + 1, j + 1) || compare(a, b, i + 1, j);
    }
    else {
        r = islower(a[i]) != 0 && compare(a, b, i + 1, j);
    }

    res[i][j] = r ? 1 : -1;
    return r;
}

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    res.clear();
    return compare(a, b) ? "YES" : "NO";
}

int main()
{
    cout << abbreviation("RDWPJPAMKGRIWAPBZSYWALDBLDOFLWIQPMPLEMCJXKAENTLVYMSJNRJAQQPWAGVcGOHEWQYZDJRAXZOYDMNZJVUSJGKKKSYNCSFWKVNHOGVYULALKEBUNZHERDDOFCYWBUCJGbvqlddfazmmohcewjg"s,
                         "RDPJPAMKGRIWAPBZSYWALDBLOFWIQPMPLEMCJXKAENTLVYMJNRJAQQPWAGVGOHEWQYZDJRAXZOYDMNZJVUSJGKKKSYNCSFWKVNHOGVYULALKEBUNZHERDOFCYWBUCJG"s) << "\n";
    cout << abbreviation("MBQEVZPBjcbswirgrmkkfvfvcpiukuxlnxkkenqp"s,
                         "MBQEVZP"s) << "\n";
    cout << abbreviation("DINVMKSOfsVQByBnCWNKPRFRKMhFRSkNQRBVNTIKNBXRSXdADOSeNDcLWFCERZOLQjEZCEPKXPCYKCVKALNxBADQBFDQUpdqunpelxauyyrwtjpkwoxlrrqbjtxlkvkcajhpqhqeitafcsjxwtttzyhzvh"s,
                         "DINVMKSOVQBBCWNKPRFRKMFRSNQRBVNTIKNBXRSXADOSNDLWFCERZOLQEZCEPKXPCYKCVKALNBADQBFDQU"s) << "\n";
    cout << abbreviation("BFZZVHdQYHQEMNEFFRFJTQmNWHFVXRXlGTFNBqWQmyOWYWSTDSTMJRYHjBNTEWADLgHVgGIRGKFQSeCXNFNaIFAXOiQORUDROaNoJPXWZXIAABZKSZYFTDDTRGZXVZZNWNRHMvSTGEQCYAJSFvbqivjuqvuzafvwwifnrlcxgbjmigkms"s,
                         "BFZZVHQYHQEMNEFFRFJTQNWHFVXRXGTFNBWQOWYWSTDSTMJRYHBNTEWADLHVGIRGKFQSCXNFNIFAXOQORUDRONJPXWZXIAABZKSZYFTDDTRGZXVZZNWNRHMSTGEQCYAJSF"s) << "\n";

    cout << abbreviation("daBcd"s, "ABC"s) << "\n";
}
