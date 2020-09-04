/*
JOI 2019 Two Dishes
- Imagine we have a grid where we start from (0, 0) and go to (N, M)
    - The "roads" represent a step of the dish being completed, so
      they have weights corresponding to the points we get
    - Notice how the weights will look like
      P[i] P[i] ... P[i] 0 0 0 0 ...
    - We can find the point that it changes to 0 by using prefix sums
- Let's focus on weighted horizontal roads first
- Plot a point with weight P[i] where the i-th column changes
  from P[i] to 0
- Notice how the score of a path is simply the sum of weights of points
  on or under that path
- dp[i][j] = Maximum score to get from (0, 0) to (i, j)
           = max(dp[i - 1][k] for k <= j) + (cost[i] if j > point in i-th column)
- We can solve for dp in O((N + M) log (N + M)) time using a lazy segtree
- If we also have weighted vertical roads, we can plot points similarly but
  count the cost if the point is above the path instead
- To make everything under the path, change the points from the vertical
  roads (x, y, v) to (x + 1, y - 1, -v) and add v to the answer initially
- Complexity: O((N + M) log (N + M))
*/

#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;

int n, m;
ll a[1000001], b[1000001];
ll s[1000001], t[1000001];
ll p[1000001], q[1000001];
pair<ll, ll> segtree[4000001];
ll lazy[4000001];

void push_lazy(int node, int l, int r) {
    segtree[node].first += lazy[node];
    segtree[node].second += lazy[node];
    if (l != r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void range_add(int a, int b, ll val, int node = 1, int l = 0, int r = m) {
    push_lazy(node, l, r);
    if (b < l || a > r) return;
    if (a <= l && b >= r) {
        lazy[node] = val;
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        range_add(a, b, val, node * 2, l, mid);
        range_add(a, b, val, node * 2 + 1, mid + 1, r);
        segtree[node].first = min(segtree[node * 2].first, segtree[node * 2 + 1].first);
        segtree[node].second = max(segtree[node * 2].second, segtree[node * 2 + 1].second);
    }
}

void range_max(int a, int b, ll val, int node = 1, int l = 0, int r = m) {
    push_lazy(node, l, r);
    if (b < l || a > r || segtree[node].first >= val) return;
    if (a <= l && b >= r && segtree[node].first == segtree[node].second) {
        lazy[node] = val - segtree[node].first;
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        range_max(a, b, val, node * 2, l, mid);
        range_max(a, b, val, node * 2 + 1, mid + 1, r);
        segtree[node].first = min(segtree[node * 2].first, segtree[node * 2 + 1].first);
        segtree[node].second = max(segtree[node * 2].second, segtree[node * 2 + 1].second);
    }
}

ll query(int pos, int node = 1, int l = 0, int r = m) {
    push_lazy(node, l, r);
    if (l == r) return segtree[node].first;
    int mid = (l + r) / 2;
    if (mid < pos) return query(pos, node * 2 + 1, mid + 1, r);
    return query(pos, node * 2, l, mid);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    ll ans = 0;
    vector<tuple<int, int, ll>> events;
    for (int i = 0; i < n; i++) {
        cin >> a[i + 1] >> s[i] >> p[i];
        a[i + 1] += a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i + 1] >> t[i] >> q[i];
        b[i + 1] += b[i];
        int x = upper_bound(a, a + n + 1, t[i] - b[i + 1]) - a;
        if (x) {
            ans += q[i];
            events.push_back({x, -i, -q[i]});
        }
    }
    for (int i = 0; i < n; i++) {
        int y = upper_bound(b, b + m + 1, s[i] - a[i + 1]) - b;
        if (y) events.push_back({i + 1, -y + 1, p[i]});
    }
    sort(events.begin(), events.end());
    for (tuple<int, int, ll> i : events) {
        int x, y, points;
        tie(x, y, points) = i;
        if (x > n) break;
        range_add(0, -y, points);
        range_max(-y, m, query(-y));
    }
    cout << ans + query(m);
    return 0;
}