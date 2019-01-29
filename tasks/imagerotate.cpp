#include <iostream>
#include <stack>
#include <array>
#include <map>
#include <list>
#include <vector>

using namespace std;

vector<vector<int>> getsubsets(const vector<int>& x, int n) {
    if (n == 2) {
        vector<int> s1 = {x[x.size() - 1]};
        vector<int> s2 = {x[x.size() - 2]};
        return {s1, s2};
    }

    vector<vector<int>> res;
    auto head = x[x.size() - n];
    res.push_back({head});

    auto sets = getsubsets(x, n - 1);
    for (auto ss: sets) {
        ss.push_back(head);
        res.push_back(ss);
    }
    res.insert(end(res), begin(sets), end(sets));
    return res;
}

void subsets() {
    vector<int> x = {1, 2, 3, 4, 5, 6, 7};

    auto s = getsubsets(x, x.size());

    for (auto i: s) {
        for (auto j: i)
            cout << j << " ";
        cout << "\n";
    }
}


struct Tree {
    int data;
    Tree* left;
    Tree* right;
};

void insert(map<int, list<Tree*>>& m, Tree* n, int level) {
    m[level].push_back(n);
}

void doLists(Tree* root) {
    map<int, list<Tree*>> m;

    int level = 0;
    insert(m, root, level);
    while(m[level].size() > 0) {
        for (auto n: m[level]) {
            if (n->left != nullptr) insert(m, n->left, level + 1);
            if (n->right != nullptr) insert(m, n->right, level + 1);
        }
        level++;
    }
}

Tree* insert(array<int, 7>& a, int s, int e) {
    if (e < s) {
        return nullptr;
    }
    int m = (s + e) / 2;
    Tree* n = new Tree{a[m], nullptr, nullptr};
    n->left = insert(a, s, m-1);
    n->right = insert(a, m+1, e);
    return n;
}

void create() {
    array<int, 7> a{1, 2, 3, 4, 5, 6, 7};

    Tree* root = insert(a, 0, a.size());
}

int minDeep(Tree* root) {
    if (root == nullptr)
        return 0;
    int left = minDeep(root->left);
    int right = minDeep(root->right);
    return min(left, right) + 1;
}

int maxDeep(Tree* root) {
    if (root == nullptr)
        return 0;
    int left = maxDeep(root->left);
    int right = maxDeep(root->right);
    return max(left, right) + 1;
}

bool isBalanced(Tree* root) {
    return maxDeep(root) - minDeep(root) <= 1;
}

void print(stack<int> st) {
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "\n";
}

void move(int n, stack<int>& src, stack<int>& dest, stack<int>& buf) {
    if (n > 0) {
        move(n - 1, src, buf, dest);
        dest.push(src.top());
        src.pop();
        move(n - 1, buf, dest, src);
    }
}

void sort(stack<int>& s, stack<int>& r) {
    while (!s.empty()) {
        auto t = s.top();
        s.pop();
        while(!r.empty() && r.top() > t) {
            s.push(r.top());
            r.pop();
        }
        r.push(t);
    }
}

int findme() {
    array<int, 10> a = {5, 6, 7, 8, 9, 10, 1, 2, 3, 4};

    auto lam = [f=a[0]](auto i, auto v) {
         if (v < f && f < i) return true;
         return i < v;
    };

    int* x = lower_bound(begin(a), end(a), 3, lam);
    return x - &a[0];
}

int main() {
    array<stack<int>, 3> st;

    constexpr int kM = 5;
    for(auto i = kM; i > 0; --i) st[0].push(i);
    print(st[0]);

//     sort(st[0], st[2]);
//     move(kM, st[0], st[2], st[1]);
//     print(st[2]);
    int v = ~0;
    int left = (v << 7);
    int right = (1 << 2) - 1;
    cout << bitset<32>(left) << "\n";
    cout << bitset<32>(right) << "\n";

    string s{"3.24"};
    auto it = s.find(".");
    string ints = s.substr(0, it);
    string decs = s.substr(it+1, string::npos);
    cout << stoi(ints) << "." << stoi(decs) << "\n";

//     subsets();
    cout << findme() << "\n";
}