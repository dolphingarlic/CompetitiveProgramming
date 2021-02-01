#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
using namespace std;
typedef long long ll;
 
const ll MOD = 1e9 + 7;
 
struct TrieNode {
    TrieNode *children[26];
    bool is_end;
 
    TrieNode() {
        FOR(i, 0, 26) children[i] = nullptr;
        is_end = false;
    }
};
 
void Insert(TrieNode *node, string s) {
    TrieNode *pCrawl = node;
    for (char i : s) {
        if (!pCrawl->children[i - 'a']) pCrawl->children[i - 'a'] = new TrieNode();
        pCrawl = pCrawl->children[i - 'a'];
    }
    pCrawl->is_end = true;
}
 
ll dp[5001];
 
TrieNode *root;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    root = new TrieNode();
    string s;
    cin >> s;
    int n = s.size(), m;
    cin >> m;
    FOR(i, 0, m) {
        string k;
        cin >> k;
        reverse(k.begin(), k.end());
        Insert(root, k);
    }
 
    dp[0] = 1;
    FOR(i, 1, n + 1) {
        TrieNode *pCrawl = root;
        for (int j = i - 1; ~j; j--) {
            if (!pCrawl->children[s[j] - 'a']) break;
            else pCrawl = pCrawl->children[s[j] - 'a'];
 
            if (pCrawl->is_end) dp[i] = (dp[i] + dp[j]) % MOD;
        }
    }
 
    cout << dp[n];
    return 0;
}
