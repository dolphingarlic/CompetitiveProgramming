/*
JOIOC 2021 Crossing
- There are at most 9 possible genomes we can get, so apply ST2's
  solution to each of them separately
- We can use a lazy segtree to check whether a given segment in
  the current query string matches a constant string
- See code for more details
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int segtree[800001];

int n, j_pref[200001][9], o_pref[200001][9], i_pref[200001][9];
char lazy[800001];
unordered_set<string> cands;
int cand_cnt;

void add_string(string s) {
    if (cands.count(s)) return;
    vector<string> to_add;
    for (string t : cands) {
        string res;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == t[i])
                res += s[i];
            else
                res += 'J' + 'O' + 'I' - s[i] - t[i];
        }
        to_add.push_back(res);
    }
    cands.insert(s);
    for (string t : to_add) add_string(t);
}

void push_lazy(int node, int l, int r) {
    if (lazy[node] == '?') return;

    segtree[node] = 0;
    if (lazy[node] == 'J') {
        for (int i = 0; i < cand_cnt; i++) {
            int j_cnt = j_pref[r][i];
            if (l) j_cnt -= j_pref[l - 1][i];
            if (j_cnt != r - l + 1) segtree[node] += 1 << i;
        }
    } else if (lazy[node] == 'O') {
        for (int i = 0; i < cand_cnt; i++) {
            int o_cnt = o_pref[r][i];
            if (l) o_cnt -= o_pref[l - 1][i];
            if (o_cnt != r - l + 1) segtree[node] += 1 << i;
        }
    } else {
        for (int i = 0; i < cand_cnt; i++) {
            int i_cnt = i_pref[r][i];
            if (l) i_cnt -= i_pref[l - 1][i];
            if (i_cnt != r - l + 1) segtree[node] += 1 << i;
        }
    }

    if (l != r)
        lazy[node * 2] = lazy[node * 2 + 1] = lazy[node];
    lazy[node] = '?';
}

void update(int x, int y, char c, int node = 1, int l = 0, int r = n - 1) {
    push_lazy(node, l, r);
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
        lazy[node] = c;
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        update(x, y, c, node * 2, l, mid);
        update(x, y, c, node * 2 + 1, mid + 1, r);
        segtree[node] = segtree[node * 2] | segtree[node * 2 + 1];
    }
}

int query(int x, int y, int node = 1, int l = 0, int r = n - 1) {
    if (l > y || r < x) return 0;
    if (l >= x && r <= y) return segtree[node];
    int mid = (l + r) / 2;
    return query(x, y, node * 2, l, mid) | query(x, y, node * 2 + 1, mid + 1, r);
}

void check() {
    for (int i = 0; i < cand_cnt; i++) if (!(segtree[1] & (1 << i))) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s1, s2, s3;
    cin >> n >> s1 >> s2 >> s3;
    add_string(s1), add_string(s2), add_string(s3);
    int idx = 0;
    cand_cnt = cands.size();
    for (string s : cands) {
        for (int i = 0; i < n; i++) {
            if (i) {
                j_pref[i][idx] = j_pref[i - 1][idx];
                o_pref[i][idx] = o_pref[i - 1][idx];
                i_pref[i][idx] = i_pref[i - 1][idx];
            }
            if (s[i] == 'J') j_pref[i][idx]++;
            else if (s[i] == 'O') o_pref[i][idx]++;
            else i_pref[i][idx]++;
        }
        idx++;
    }
    fill_n(lazy + 1, 4 * n, '?');

    int q;
    string sq;
    cin >> q >> sq;
    for (int i = 0; i < n; i++) update(i, i, sq[i]);
    check();
    while (q--) {
        int l, r;
        char c;
        cin >> l >> r >> c;
        l--, r--;
        update(l, r, c);
        check();
    }
    return 0;
}
