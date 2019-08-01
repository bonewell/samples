//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <list>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& v)
{
    for (const auto& r: v) {
        for (int i: r) {
            cout << i << " ";
        }
        cout << "\n";
    }
    return out;
}

struct Node
{
    explicit Node(int d) : data{d} {}
    int data{0};
    unique_ptr<Node> left{nullptr};
    unique_ptr<Node> right{nullptr};
};

unique_ptr<Node> create(const vector<vector<int>>& indexes)
{
    auto tree = make_unique<Node>(1);
    list<Node*> nodes;
    nodes.push_back(tree.get());
    auto it = begin(nodes);
    for (const auto& children: indexes) {
        auto node = *it;
        if (children[0] != -1) {
            node->left = make_unique<Node>(children[0]);
            nodes.push_back(node->left.get());
        }
        if (children[1] != -1) {
            node->right = make_unique<Node>(children[1]);
            nodes.push_back(node->right.get());
        }
        ++it;
    }
    return tree;
}

void swap(Node* node, int k, int l = 1)
{
    if (!node) return;

    if (l % k == 0) {
        swap(node->left, node->right);
    }
    swap(node->left.get(), k, l+1);
    swap(node->right.get(), k, l+1);
}

vector<int> traverse(const Node& node)
{
    vector<int> res;
    if (node.left) {
        auto left_subtree = traverse(*node.left);
        res.insert(end(res), begin(left_subtree), end(left_subtree));
    }
    res.push_back(node.data);
    if (node.right) {
        auto right_subtree = traverse(*node.right);
        res.insert(end(res), begin(right_subtree), end(right_subtree));
    }
    return res;
}

/*
 * Complete the swapNodes function below.
 */
vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries)
{
    auto tree = create(indexes);
    vector<vector<int>> res;
    res.push_back(traverse(*tree));
    for (auto q: queries) {
        swap(tree.get(), q);
        res.push_back(traverse(*tree));
    }
    return res;
}

int main()
{
//    vector<vector<int>> indexes{{2, 3}, {-1, -1}, {-1, -1}};
    vector<vector<int>> indexes{{2, 3}, {4, -1}, {5, -1}, {6, -1},
        {7, 8}, {-1, 9}, {-1, -1}, {10, 11}, {-1, -1}, {-1, -1}, {-1, -1}};
//    vector<int> queries{1, 1};
    vector<int> queries{2, 4};
    cout << swapNodes(indexes, queries) << "\n";
}
