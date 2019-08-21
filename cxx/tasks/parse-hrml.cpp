//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <utility>
using namespace std;

using Attributes = unordered_map<string, string>;
using Tag = pair<string, Attributes>;
using Document = unordered_map<string, string>;

class Hrml {
public:
    void parse(const string& line) {
        if (line[0] == '<' && line[1] == '/') {
            tree_.pop_back();
        }
        else if (line[0] == '<') {
            auto t = tag(line);
            for (const auto& a: t.second) {
                doc_.emplace(fullname(a.first), a.second);
            }
            tree_.push_back(t.first);
        }
    }
    string get(const string& name) {
        auto it = doc_.find(name);
        if (it != doc_.end()) {
            return it->second;
        }
        else
            return "Not Found!";
    }
    void print() {
        for (const auto& p: doc_) {
            cout << p.first << '=' << p.second << '\n';
        }
    }
private:
    Tag tag(const string& line) const;
    string fullname(const string& name) const;
    vector<string> tree_;
    Document doc_;
};

Tag Hrml::tag(const string& line) const {
    istringstream iss{line.substr(1, line.length() - 2)};
    string tag_name;
    iss >> tag_name;
    Attributes attributes;
    while (!iss.eof()) {
        string name, op, value;
        iss >> name >> op >> value;
        attributes.emplace(tag_name + '~' + name, value.substr(1, value.length() - 2));
    }
    return make_pair(tag_name, attributes);
}

string Hrml::fullname(const string& name) const {
    string fullname;
    for (const auto& n: tree_) {
        fullname += n + '.';
    }
    fullname += name;
    return fullname;
}

int main() {
    int n, q = 0;
    cin >> n >> q;
    string stub;
    getline(cin, stub);

    Hrml doc;
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        doc.parse(line);
    }

//    doc.print();

    for (int i = 0; i < q; ++i) {
        string line;
        getline(cin, line);
        cout << doc.get(line) << '\n';
    }

    return 0;
}
