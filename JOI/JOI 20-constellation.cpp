/*
JOI 2020 Constellation
- Let dp[i][j] = Maximum sum of remaining stars if we choose NOT to paint cell (i, j)
                 for the first i rows from the bottom
    - If there is no star on (i, j), just pretend there is and give it a value of 0
    - Also, add an imaginary row N + 1 with no stars
    - The answer is (sum of all values) - max_element(dp[N + 1])
- Notice how if there are 2 stars (x, y1) = v1 and (x, y2) = v2 where y1 > y2 and v1 <= v2,
  we will always choose to paint (x, y1) since the set of constellations with (x, y2) is a
  subset of the set of constellations with (x, y1)
- Assume WLOG that the stars' values are monotonic from bottom to top for each column
- For column, replace star X's value with star X's value - star (X - 1)'s value
    - (star 0's value = 0)
- Notice how dp[i] depends only on dp[i - 1] and the stars in row i
    - Drop the first dimension
- Next, if we go from the bottom up, we get some connected components which may merge with each other
- Notice how if we merge 2 components (assume for simplicity that there are no stars in that row),
  we add the maximum dp value of each component to each cell of the other
- If there are stars though, simply add their values to their respective cells AFTER merging the components
    - This works because before adding the value to (x, y), we're assuming that dp[y] is the maximum sum
      if we remove all stars that can make a constellation with (x, y)
    - Since we did that star X - star (X - 1) thing earlier, this means that we won't end up with 2 stars
      in the same column
- To speed this up, we can use a lazy segment tree and DSU
- Complexity: O((N + M) log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m;
ll ans = 0;

ll segtree[800001], lazy[800001];

void push_lazy(int node, int l, int r) {
    segtree[node] += lazy[node];
    if (l != r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int a, int b, ll val, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
        lazy[node] = val;
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        update(a, b, val, node * 2, l, mid);
        update(a, b, val, node * 2 + 1, mid + 1, r);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

ll query(int a, int b, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return segtree[node];
    int mid = (l + r) / 2;
    return max(query(a, b, node * 2, l, mid), query(a, b, node * 2 + 1, mid + 1, r));
}

int cmp[200001];
pair<int, int> range[200001];

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    A = find(A), B = find(B);
    range[A].first = min(range[A].first, range[B].first);
    range[A].second = max(range[A].second, range[B].second);
    cmp[B] = A;
}

bool active[200001];

int a[200001];
vector<int> cmp_start[200002];
vector<pair<int, ll>> col[200001], row[200001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        cmp_start[a[i] + 1].push_back(i);
    }
    cin >> m;
    FOR(i, 1, m + 1) {
        int x, y;
        ll v;
        cin >> x >> y >> v;
        col[x].push_back({y, v});
        ans += v;
    }

    FOR(i, 1, n + 1) {
        sort(col[i].begin(), col[i].end());
        vector<pair<int, ll>> keep;
        ll last = 0;
        for (pair<int, ll> j : col[i]) if (j.second > last) {
            keep.push_back(j);
            last = j.second;
        }
        last = 0;
        for (pair<int, ll> j : keep) {
            row[j.first].push_back({i, j.second - last});
            last = j.second;
        }
    }

    iota(cmp + 1, cmp + n + 1, 1);
    FOR(i, 1, n + 1) range[i] = {i, i};

    FOR(i, 1, n + 1) {
        for (int x : cmp_start[i]) {
            ll l_mx = 0, r_mx = 0, dp = 0;

            if (x - 1 && active[x - 1]) {
                l_mx = query(range[find(x - 1)].first, range[find(x - 1)].second);
                dp += l_mx;
            }
            if (x + 1 <= n && active[x + 1]) {
                r_mx = query(range[find(x + 1)].first, range[find(x + 1)].second);
                dp += r_mx;
            }

            if (x - 1 && active[x - 1])
                update(range[find(x - 1)].first, range[find(x - 1)].second, r_mx);
            if (x + 1 <= n && active[x + 1])
                update(range[find(x + 1)].first, range[find(x + 1)].second, l_mx);

            if (x - 1 && active[x - 1]) onion(x - 1, x);
            if (x + 1 <= n && active[x + 1]) onion(x, x + 1);
            active[x] = true;
            update(x, x, dp);
        }
        
        for (pair<int, ll> star : row[i]) update(star.first, star.first, star.second);
    }

    ll mx = 0;
    FOR(i, 1, n + 1) {
        if (a[i] == n) {
            ans -= mx;
            mx = 0;
        } else mx = max(mx, query(i, i));
    }
    ans -= mx;
    cout << ans;
    return 0;
}