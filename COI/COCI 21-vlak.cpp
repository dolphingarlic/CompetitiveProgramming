#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct TrieNode {
    TrieNode *children[26];
    int good_for;
    bool can_win;

    TrieNode(): good_for(0), can_win(false) {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }

    void dfs(int curr_player) {
        if (good_for & curr_player) {
            for (int i = 0; i < 26; i++) if (children[i]) {
                children[i]->dfs(3 - curr_player);
                can_win |= !children[i]->can_win;
            }
        }
    }
};

void insert(TrieNode *root, string key, int player) {
    TrieNode *pCrawl = root;
    pCrawl->good_for |= player;
    for (char c : key) {
        int idx = c - 'a';
        if (!pCrawl->children[idx]) pCrawl->children[idx] = new TrieNode();
        pCrawl = pCrawl->children[idx];
        pCrawl->good_for |= player;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    TrieNode *root = new TrieNode();
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        insert(root, s, 1);
    }
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        insert(root, s, 2);
    }
    root->dfs(1);
    cout << (root->can_win ? "Nina" : "Emilija");
    return 0;
}