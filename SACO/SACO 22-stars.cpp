#include <iostream>
#include <algorithm>
using namespace std;

struct TrieNode {
    TrieNode *children[2];
    int subtree_size = 0;

    TrieNode() {
        children[0] = children[1] = nullptr;
    }
};

int n, r, x[100001];

void insert(TrieNode *root, int val) {
    TrieNode *node = root;
    for (int i = 30; ~i; i--) {
        int bit = (val >> i) & 1;
        if (!node->children[bit])
            node->children[bit] = new TrieNode();
        node = node->children[bit];
        node->subtree_size++;
    }
}

int num_covered(TrieNode *root, int pos) {
    TrieNode *node = root;
    int ans = 0;
    for (int i = 30; ~i && node; i--) {
        int bit = (pos >> i) & 1;
        if ((r >> i) & 1) {
            if (node->children[bit]) ans += node->children[bit]->subtree_size;
            node = node->children[!bit];
        } else node = node->children[bit];
    }
    if (node) ans++;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> r;
    TrieNode *root = new TrieNode();
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        insert(root, x[i]);
    }
    int best_coverage = 0, best_pos = -1;
    sort(x, x + n);
    for (int i = 0; i < n; i++) {
        int coverage = num_covered(root, x[i]);
        if (coverage > best_coverage) {
            best_coverage = coverage;
            best_pos = x[i];
        }
    }
    cout << best_pos;
    return 0;
}
