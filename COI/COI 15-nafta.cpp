/*
COI 2015 Nafta
- First, flatten the grid so that we get a bunch of weighted intervals
- Notice how if A and B both cover some interval, then so do A and C where B < C < A
- This gives us the following DP state:
    dp[i][j] = Max oil we can get if we've placed i drills and the last drill is on j
             = max(dp[i - 1][k] + (Sum of intervals that j covers but k doesn't))
- We can precompute (Sum of intervals that j covers but k doesn't) in O(N^2 log N)
  using a BIT and a line sweep
- Next, notice that the optimal k for (i, j) is never less than the optimal k for (i, j - 1)
- This means that we can use D&C DP to solve the recurrence efficiently
- Complexity: O(N^2 log N)
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
char grid[2001][2001];
bool visited[2001][2001];
int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};
int bit[2001], diff[2001][2001], dp[2001][2001];

bool inside(int x, int y) {
    return x && y && x <= n && y <= m && !visited[x][y] && grid[x][y] != '.';
}

tuple<int, int, int> get_oil(int x, int y) {
    tuple<int, int, int> ret = {y, y, grid[x][y] - '0'};
    visited[x][y] = true;
    for (int i = 0; i < 4; i++) if (inside(x + dx[i], y + dy[i])) {
        tuple<int, int, int> pot = get_oil(x + dx[i], y + dy[i]);
        get<0>(ret) = min(get<0>(ret), get<0>(pot));
        get<1>(ret) = max(get<1>(ret), get<1>(pot));
        get<2>(ret) += get<2>(pot);
    }
    return ret;
}

void update(int pos, int val) {
    for (; pos <= m; pos += pos & -pos) bit[pos] += val;
}

int query(int pos) {
    int ans = 0;
    for (; pos; pos -= pos & -pos) ans += bit[pos];
    return ans;
}

void solve(int placed, int l = 1, int r = m, int opt_l = 0, int opt_r = m - 1) {
    int mid = (l + r) / 2;
    int opt = -1;
    for (int i = opt_l; i <= min(mid - 1, opt_r); i++) {
        if (dp[placed - 1][i] + diff[mid][i] > dp[placed][mid]) {
            dp[placed][mid] = dp[placed - 1][i] + diff[mid][i];
            opt = i;
        }
    }
    if (l != r) {
        solve(placed, l, mid, opt_l, opt);
        solve(placed, mid + 1, r, opt, opt_r);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        cin >> grid[i][j];
    }
    vector<tuple<int, int, int>> oil;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        if (inside(i, j)) {
            int l, r, val;
            tie(l, r, val) = get_oil(i, j);
            oil.push_back({l, l, val});
            oil.push_back({r + 1, l, -val});
        }
    }
    sort(oil.begin(), oil.end());
    for (int i = 1, ptr = 0; i <= m; i++) {
        while (get<0>(oil[ptr]) <= i) {
            update(get<1>(oil[ptr]), get<2>(oil[ptr]));
            ptr++;
        }
        for (int j = 0; j < i; j++) diff[i][j] = query(i) - query(j);
    }
    for (int i = 1; i <= m; i++) {
        solve(i);
        cout << *max_element(dp[i] + 1, dp[i] + m + 1) << '\n';
    }
    return 0;
}