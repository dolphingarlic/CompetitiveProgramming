#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Query {
    bool add;
    int a, b;
} queries[200001];

vector<int> graph[200001];
int to_root[200001], tin[200001], tout[200001], timer = 0;

void dfs(int node = 1) {
    tin[node] = ++timer;
    for (int i : graph[node]) dfs(i);
    tout[node] = timer;
}

struct TrieNode {
    TrieNode *children[2];
    set<int> ids;

    TrieNode() {
        children[0] = nullptr;
        children[1] = nullptr;
    }
};

void insert(TrieNode *root, int val, int node) {
    TrieNode *pCrawl = root;
    for (int i = 30; ~i; i--) {
        int idx = ((val & (1 << i)) != 0);
        if (!pCrawl->children[idx]) pCrawl->children[idx] = new TrieNode();
        pCrawl = pCrawl->children[idx];
        pCrawl->ids.insert(tin[node]);
    }
}

int query(TrieNode *root, int val, int subtree) {
    int ans = 0;
    TrieNode *pCrawl = root;
    for (int i = 30; ~i; i--) {
        int idx = ((val & (1 << i)) == 0);
        if (pCrawl->children[idx]) {
            auto lb = pCrawl->children[idx]->ids.lower_bound(tin[subtree]);
            if (lb != pCrawl->children[idx]->ids.end() && *lb <= tout[subtree]) {
                ans |= (1 << i);
                pCrawl = pCrawl->children[idx];
            } else pCrawl = pCrawl->children[1 - idx];
        } else pCrawl = pCrawl->children[1 - idx];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> q;

    int n = 1;
    FOR(i, 0, q) {
        string type;
        int a, b;
        cin >> type >> a >> b;
        queries[i] = {(type == "Add"), a, b};
        if (type == "Add") graph[a].push_back(++n);
    }
    dfs();

    TrieNode *root = new TrieNode();
    n = 1;
    insert(root, 0, 1);
    FOR(i, 0, q) {
        if (queries[i].add) {
            to_root[++n] = to_root[queries[i].a] ^ queries[i].b;
            insert(root, to_root[n], n);
        } else {
            cout << query(root, to_root[queries[i].a], queries[i].b) << endl;
        }
    }
    return 0;
}