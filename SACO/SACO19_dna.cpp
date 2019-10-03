#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
using namespace std;
typedef long long ll;

map<char, int> val = {{'A', 0}, {'T', 1}, {'C', 2}, {'G', 3}};

struct TrieNode {
    TrieNode *children[4];
    bool is_end;

    TrieNode() {
        FOR(i, 0, 4) children[i] = nullptr;
        is_end = false;
    }
};

void Insert(TrieNode *node, string s) {
    TrieNode *pCrawl = node;
    for (char i : s) {
        if (!pCrawl->children[val[i]]) pCrawl->children[val[i]] = new TrieNode();
        pCrawl = pCrawl->children[val[i]];
    }
    pCrawl->is_end = true;
}

ll dp[5001], l[100001];
string k[100001];

TrieNode *root;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    root = new TrieNode();
    int n, m;
    string s;
    cin >> n >> m >> s;
    FOR(i, 0, m) {
        cin >> l[i] >> k[i];
        reverse(k[i].begin(), k[i].end());
        Insert(root, k[i]);
    }

    dp[0] = 0;
    FOR(i, 1, n + 1) {
        dp[i] = (1ll << 60);
        TrieNode *pCrawl = root;
        for (int j = i - 1; ~j; j--) {
            if (!pCrawl->children[val[s[j]]]) break;
            else pCrawl = pCrawl->children[val[s[j]]];

            if (pCrawl->is_end) dp[i] = min(dp[i], dp[j] + 1);
        }
    }

    if (dp[n] == (1ll << 60)) cout << -1 << '\n';
    else cout << dp[n] << '\n';
    return 0;
}