#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
#define ALPHABET 26
typedef long long ll;
using namespace std;

vector<char> ops;
string longest = "", words[25000];

bool cmp(string a, string b) {
    return (a.length() < b.length());
}

struct TrieNode {
    TrieNode *children[ALPHABET];
    bool isEndOfWord, containsLongest;
};

TrieNode *getNode() {
    TrieNode *pNode = new TrieNode;
    pNode->isEndOfWord = false;
    pNode->containsLongest = false;
    FOR(i, 0, ALPHABET) pNode->children[i] = NULL;
    return pNode;
}

void insert(TrieNode *root, string key) {
    TrieNode *pCrawl = root;

    FOR(i, 0, key.length()) {
        int indx = key[i] - 'a';
        if (!pCrawl->children[indx]) pCrawl->children[indx] = getNode();
        pCrawl = pCrawl->children[indx];
    }
    pCrawl->isEndOfWord = true;
}

void insertLongest(TrieNode *root) {
    TrieNode *pCrawl = root;
    pCrawl->containsLongest = true;

    FOR(i, 0, longest.length()) {
        int indx = longest[i] - 'a';
        if (!pCrawl->children[indx]) pCrawl->children[indx] = getNode();
        pCrawl = pCrawl->children[indx];
        pCrawl->containsLongest = true;
    }
    pCrawl->isEndOfWord = true;
}

void dfs(TrieNode *root) {
    if (root->isEndOfWord) ops.push_back('P');
    if (root->containsLongest) {
        FOR(i, 0, ALPHABET) {
            if (root->children[i] && !(root->children[i]->containsLongest)) {
                ops.push_back(i + 'a');
                dfs(root->children[i]);
                ops.push_back('-');
            }
        }
        FOR(i, 0, ALPHABET) {
            if (root->children[i] && root->children[i]->containsLongest) {
                ops.push_back(i + 'a');
                dfs(root->children[i]);
            }
        }
    } else {
        FOR(i, 0, ALPHABET) {
            if (root->children[i]) {
                ops.push_back(i + 'a');
                dfs(root->children[i]);
                ops.push_back('-');
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    TrieNode *root = getNode();
    FOR(i, 0, n) {
        cin >> words[i];
    }
    sort(words, words + n, cmp);
    FOR(i, 0, n - 1) {
        insert(root, words[i]);
    }
    longest = words[n - 1];
    insertLongest(root);

    dfs(root);
    cout << ops.size() << '\n';
    for (char i : ops) cout << i << '\n';
    return 0;
}