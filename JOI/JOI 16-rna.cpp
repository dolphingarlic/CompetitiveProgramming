#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode *c[4];
    int tin, tout;
    vector<int> terminal;
    vector<tuple<int, int, int>> queries;
    unordered_map<int, int> bit;

    TrieNode() {
        for (int i = 0; i < 4; i++) c[i] = nullptr;
    }
};

inline int get_idx(char c) {
    if (c == 'A') return 0;
    if (c == 'G') return 1;
    if (c == 'C') return 2;
    return 3;
}

void insert(string &s, TrieNode *node, int i) {
    for (char c : s) {
        int idx = get_idx(c);
        if (!node->c[idx]) node->c[idx] = new TrieNode();
        node = node->c[idx];
    }
    node->terminal.push_back(i);
}

TrieNode *retrieve(string &s, TrieNode *node) {
    for (char c : s) {
        int idx = get_idx(c);
        if (!node->c[idx]) return nullptr;
        node = node->c[idx];
    }
    return node;
}

int n, m, label[100001];
vector<int> comp;

void euler_tour(TrieNode *node, int &timer) {
    node->tin = ++timer;
    if (node->terminal.size()) {
        for (int i : node->terminal) label[i] = timer;
        comp.push_back(timer);
    }
    for (int i = 0; i < 4; i++)
        if (node->c[i]) euler_tour(node->c[i], timer);
    node->tout = timer;
}

int ans[100001];

void merge(TrieNode *A, TrieNode *B) {
    if (A->bit.size() > B->bit.size()) swap(A->bit, B->bit);
    for (pair<int, int> i : A->bit) B->bit[i.first] += i.second;
}

int find_lb(int val) {
    return lower_bound(comp.begin(), comp.end(), val) - comp.begin() + 1;
}

int find_ub(int val) {
    return upper_bound(comp.begin(), comp.end(), val) - comp.begin();
}

void update(unordered_map<int, int> &bit, int pos, int val) {
    for (; pos <= comp.size(); pos += pos & -pos) bit[pos] += val;
}

int query(unordered_map<int, int> &bit, int l, int r) {
    int ans = 0;
    for (; r; r -= r & -r) ans += bit[r];
    for (l--; l; l -= l & -l) ans -= bit[l];
    return ans;
}

void traverse(TrieNode *node) {
    for (int i = 0; i < 4; i++)
        if (node->c[i]) {
            traverse(node->c[i]);
            merge(node->c[i], node);
        }
    for (int i : node->terminal) update(node->bit, find_lb(label[i]), 1);

    for (auto i : node->queries) {
        int idx, l, r;
        tie(idx, l, r) = i;
        ans[idx] = query(node->bit, find_lb(l), find_ub(r));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    TrieNode *pref = new TrieNode(), *suff = new TrieNode();
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        insert(s, pref, i);
        reverse(s.begin(), s.end());
        insert(s, suff, i);
    }

    int timer = 0;
    euler_tour(pref, timer);

    for (int i = 1; i <= m; i++) {
        string s, t;
        cin >> s >> t;
        reverse(t.begin(), t.end());
        TrieNode *s_node = retrieve(s, pref), *t_node = retrieve(t, suff);
        if (s_node && t_node)
            t_node->queries.push_back({i, s_node->tin, s_node->tout});
    }

    traverse(suff);
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
}
