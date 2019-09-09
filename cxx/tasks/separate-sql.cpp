#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

vector<string> separate(string const& sql)
{
    vector<string> res;

    int b{0};
    bool str{false};
    for (int i = 0; i < sql.length(); ++i) {
        if (sql[i] == '\'') {
            str = !str;
        }
        else if (sql[i] == ';' && !str) {
            res.push_back(sql.substr(b, i - b));
            b = i + 1;
        }
    }
    if (sql[sql.length() - 1] != ';') {
        res.push_back(sql.substr(b));
    }

    return res;
}

int main()
{
    auto res1 = separate("SELECT * FROM table;SELECT * FROM table2");
    copy(begin(res1), end(res1), ostream_iterator<string>{cout, "\n"});

    auto res2 = separate("SELECT * FROM user;SELECT * FROM user2");
    copy(begin(res2), end(res2), ostream_iterator<string>{cout, "\n"});

    auto res3 = separate("SELECT * FROM user WHERE name='ab;cd';SELECT * FROM user2");
    copy(begin(res3), end(res3), ostream_iterator<string>{cout, "\n"});

    return 0;
}
