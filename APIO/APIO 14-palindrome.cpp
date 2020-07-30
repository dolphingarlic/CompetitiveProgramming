/*
APIO 2014 Palindrome
- First, construct the palindrome tree from the string
    - In addition to the standard information we store in each node,
      store the number of times each palindrome was the maximum suffix
    - Let this amount be node.count
- The answer is simply the maximum
  node.length * sum(child.count for each child in node's subtree)
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    int nxt[26], sufflink;
    ll len, cnt;
    vector<int> edges;
} tree[303030];

string s;
int suff, num;
ll ans = 0;

void add_letter(int pos) {
    int curr = suff, curr_len = 0;
    int letter = s[pos] - 'a';

    while (true) {
        curr_len = tree[curr].len;
        if (pos - 1 - curr_len > -1 && s[pos - 1 - curr_len] == s[pos])
            break;
        curr = tree[curr].sufflink;
    }
    if (tree[curr].nxt[letter]) {
        suff = tree[curr].nxt[letter];
        tree[suff].cnt++;
        return;
    }
    
    suff = ++num;
    tree[num].len = tree[curr].len + 2;
    tree[num].cnt = 1;
    tree[curr].nxt[letter] = num;

    if (tree[num].len == 1) {
        tree[num].sufflink = 2;
        tree[2].edges.push_back(num);
        return;
    }

    while (true) {
        curr = tree[curr].sufflink;
        curr_len = tree[curr].len;
        if (pos - 1 - curr_len > -1 && s[pos - 1 - curr_len] == s[pos]) {
            tree[num].sufflink = tree[curr].nxt[letter];
            tree[tree[curr].nxt[letter]].edges.push_back(num);
            break;
        }
    }
}

void init() {
    num = 2, suff = 2;
    tree[1].len = -1, tree[1].sufflink = 1;
    tree[2].len = 0, tree[2].sufflink = 1;
    tree[1].edges.push_back(2);
}

void dfs(int node = 1) {
    for (int i : tree[node].edges) {
        dfs(i);
        tree[node].cnt += tree[i].cnt;
    }
    ans = max(ans, tree[node].len * tree[node].cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    init();
    FOR(i, 0, s.size()) add_letter(i);
    dfs();
    cout << ans;
    return 0;
}