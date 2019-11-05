#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int nodes = 1;

struct TrieNode {
    TrieNode *children[26];
    bool isEnd;
    int cnt;

    TrieNode() {
        isEnd = false;
        FOR(i, 0, 26) children[i] = NULL;
        cnt = 0;
    }
};

void insert(TrieNode *root, string key) {
    TrieNode *pCrawl = root;

    FOR(i, 0, key.length()) {
        int indx = key[i] - 'A';
        pCrawl->cnt++;
        if (!pCrawl->children[indx]) {
            pCrawl->children[indx] = new TrieNode();
            nodes++;
        }
        pCrawl = pCrawl->children[indx];
    }
    pCrawl->isEnd = true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    TrieNode *trie = new TrieNode();
    while (cin >> s) insert(trie, s);
    cout << nodes << '\n';
    return 0;
}