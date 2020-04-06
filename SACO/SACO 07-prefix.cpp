#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

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
        if (!pCrawl->children[indx]) pCrawl->children[indx] = new TrieNode();
        pCrawl = pCrawl->children[indx];
    }
    pCrawl->isEnd = true;
}

string ans;
int max_len = 0;
void dfs(TrieNode *root, int depth, string curr) {
    if (max_len < depth) ans = curr, max_len = depth;
    FOR(i, 0, 26) {
        if (root->children[i] && root->children[i]->cnt > 1) {
            dfs(root->children[i], depth + 1, curr + (char)(i + 'A'));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    
    TrieNode *trie = new TrieNode();
    FOR(i, 0, n) {
        string s;
        cin >> s;
        insert(trie, s);
    }

    FOR(i, 0, 26)
        if (trie->children[i] && trie->children[i]->cnt > 1)
            dfs(trie->children[i], 1, string(1, i + 'A'));

    cout << ans;
    return 0;
}