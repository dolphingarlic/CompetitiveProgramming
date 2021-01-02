/*
Balkan 2019 Dictionary
- Consider the prefixes of the polynomial hash
- A word [l, r] has a hash of 0 iff pref[r] == pref[l - 1]
- Since we want shortest words, we only consider [l, r] if
  there are no indices l <= k < r with pref[k] == pref[r]
    - Otherwise, [l, r] will never be optimal: any range that
      contains it also contains [k + 1, r], which is shorter
- This means there are O(L) potential words
- We can now rephrase the problem as "given N segments on the
  number line, answer queries that ask for the shortest segment
  completely contained in a range"
- We can solve the above problem using a persistent segment tree
- Let the right endpoint represent the time that a segment (now
  represented by a point from its left endpoint) is inserted
- Queries work similarly - now it's just standard RMQ
- Complexity: O((L + Q) log L)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const pair<int, int> MN = {INT_MAX, -1};

struct Node {
    Node *l, *r;
    pair<int, int> val;

    Node(pair<int, int> _val) {
        l = r = nullptr;
        val = _val;
    }

    Node(Node *_l, Node *_r) {
        l = _l, r = _r;
        val = {INT_MAX, -1};
        if (l) val = min(val, l->val);
        if (r) val = min(val, r->val);
    }
};

ll a, m;
int n, q;
vector<pair<int, int>> words[200001];
Node *persist_roots[200001];

Node* build(int l = 1, int r = n) {
    if (l == r) return new Node(MN);
    int mid = (l + r) / 2;
    return new Node(build(l, mid), build(mid + 1, r));
}

pair<int, int> query(Node* node, int a, int b, int l = 1, int r = n) {
    if (l > b || r < a) return MN;
    if (l >= a && r <= b) return node->val;
    int mid = (l + r) / 2;
    return min(query(node->l, a, b, l, mid), query(node->r, a, b, mid + 1, r));
}

Node* update(Node* node, int pos, pair<int, int> val, int l = 1, int r = n) {
    if (l == r) return new Node(val);
    int mid = (l + r) / 2;
    if (pos > mid) return new Node(node->l, update(node->r, pos, val, mid + 1, r));
    else return new Node(update(node->l, pos, val, l, mid), node->r);
}

int main() {
    cin >> a >> m >> n >> q;
    ll curr_hsh = 0, curr_pw = 1;
    map<ll, vector<int>> has_hsh;
    has_hsh[0].push_back(0);
    for (int i = 1; i <= n; i++) {
        ll t;
        cin >> t;
        curr_hsh = (curr_hsh + curr_pw * t) % m;
        curr_pw = curr_pw * a % m;
        has_hsh[curr_hsh].push_back(i);
    }

    for (auto& i : has_hsh)
        for (int j = 1; j < i.second.size(); j++)
            words[i.second[j]].push_back({i.second[j] - i.second[j - 1], i.second[j - 1] + 1});
    persist_roots[0] = build();
    for (int i = 1; i <= n; i++) {
        persist_roots[i] = persist_roots[i - 1];
        for (pair<int, int> j : words[i])
            persist_roots[i] = update(persist_roots[i], j.second, j);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        pair<int, int> ans = query(persist_roots[r], l, r);
        if (ans.second == -1) cout << -1 << endl;
        else cout << ans.second << ' ' << ans.second + ans.first - 1 << endl;
    }
    return 0;
}
