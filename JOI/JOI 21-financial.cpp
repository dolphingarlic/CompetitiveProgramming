/*
JOIOC 2021 Financial Report
- Let leftmost[i] be the leftmost index j such that the range
  [j, i] doesn't contain D consecutive days k where A[k] >= A[i]
    - We can compute this array by iterating through the days in
      decreasing order of A[i], and using DSU and a max segtree
- Let dp[i] be the answer if we want the report to end of day i
  instead of day N
    - Clearly, the answer is max(dp[i]) because we can always
      extend the presentation to day N without any penalty
    - dp[i] = max(dp[j] : j in [leftmost[i], i - 1]) + 1
    - Again, we use a segtree to compute this array
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, d, a[300001], leftmost[300001];
int cmp[300001], sz[300001], segtree[1200001];
vector<pair<int, int>> ord;

int query(int x, int y, int node = 1, int l = 1, int r = n) {
    if (l > y || r < x) return 0;
    if (l >= x && r <= y) return segtree[node];
    int mid = (l + r) / 2;
    return max(query(x, y, node * 2, l, mid), query(x, y, node * 2 + 1, mid + 1, r));
}

void update(int pos, int val, int node = 1, int l = 1, int r = n) {
    if (l == r) segtree[node] = val;
    else {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, node * 2 + 1, mid + 1, r);
        else update(pos, val, node * 2, l, mid);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

int find(int A) { return cmp[A] = (A == cmp[A] ? A : find(cmp[A])); }

void onion(int A, int B) {
    A = find(A), B = find(B);
    if (A == B) return;
    sz[B] += sz[A];
    cmp[A] = B;
    if (sz[B] >= d) update(B, B);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> d;
    vector<pair<int, int>> ord;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ord.push_back({-a[i], i});
    }
    sort(ord.begin(), ord.end());

    iota(cmp + 1, cmp + n + 1, 1);
    fill_n(sz + 1, n, 1);
    for (pair<int, int> i : ord) {
        leftmost[i.second] = query(1, i.second) + 1;
        if (d == 1) update(i.second, i.second);
        if (i.second != n && a[i.second] < a[i.second + 1])
            onion(i.second, i.second + 1);
        if (i.second != 1 && a[i.second] <= a[i.second - 1])
            onion(i.second - 1, i.second);
    }

    reverse(ord.begin(), ord.end());
    memset(segtree, 0, sizeof segtree);
    int ans = 0;
    for (pair<int, int> i : ord) {
        int pot = query(leftmost[i.second], i.second) + 1;
        update(i.second, pot);
        ans = max(ans, pot);
    }
    cout << ans;
    return 0;
}
