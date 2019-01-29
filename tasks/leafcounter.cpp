#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    Node* left{nullptr};
    Node* right{nullptr};
    int data{};
};

bool isLeaf(Node* node) {
    return node->left == nullptr && node->right == nullptr;
}

bool hasLeftLeaf(Node* node) {
    return node->left != nullptr && isLeaf(node->left);
}

int count(Node* node) {
    if (node == nullptr) return 0;
    int rc = count(node->right);
    int lc = hasLeftLeaf(node) ? 1 : count(node->left);
    return lc + rc;
}

int countleft(Node* node) {
    if (node == nullptr) return 0;

    unordered_map<int, Node*> v{{0, node}};
    int c = 0;
    int i = 0;
    int j = 1;
    while (i < j) {
        if (hasLeftLeaf(v[i])) ++c;
        if (v[i]->left != nullptr) v[j++] = v[i]->left;
        if (v[i]->right != nullptr) v[j++] = v[i]->right;
        v.erase(i);
        ++i;
    }
    return c;
}

int main() {
    Node tree;
    Node left, right;
    Node leftleft, leftright;
    Node rightleft, rightright;
    Node leftleftleft, leftleftright;

    rightright.left = &leftleftleft;
    left.left = &leftleft;
    left.right = &leftright;
    right.left = &rightleft;
    right.right = &rightright;
    tree.left = &left;
    tree.right = &right;

    int c = count(&tree);
    cout << c << "\n";

    int cnt = countleft(&tree);
    cout << cnt << "\n";
}