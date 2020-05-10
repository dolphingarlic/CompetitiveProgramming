/*
POI 2006 Frogs
- First, we find the minimum squared distance to each scarefrog for each square
- v[i][j] = Minimum distance to a scarefrog in the same column as square (i, j)
- dp[i][j] = Minimum squared distance to each scarefrog for square (i, j)
           = min((j - k)^2 + v[i][k]^2) for each k
- Consider only k < j for now
- Notice how the equation is a parabola, which is convex
- This means we can use CHT to solve for dp efficiently (since if A < B and B is better than A,
  then A is never the optimal k again)
- Next, we simply use Dijkstra or binary search + DFS to find the frogshold distance
- Complexity: O(NM log NM)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define X first
#define Y second
typedef long long ll;
using namespace std;

int n, m, k;
pair<int, int> src, dest;
ll l, r, mid;

int v[1002][1002], dq[1002];
ll dp[1002][1002];
bool visited[1002][1002];
vector<pair<int, int>> mv = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

inline ll sq(int x) { return ll(x) * x; }

inline bool case_1(int a, int b, int c, int i) {
    return sq(b) - sq(a) + sq(v[i][b]) - sq(v[i][a]) <= 2 * c * (b - a);
}

inline bool case_2(int a, int b, int c, int i) {
    return (sq(b) - sq(a) + sq(v[i][b]) - sq(v[i][a])) * (c - b) >=
           (sq(c) - sq(b) + sq(v[i][c]) - sq(v[i][b])) * (b - a);
}

inline bool good(int x, int y) {
    return (x && y && x <= n && y <= m && dp[x][y] >= mid && !visited[x][y]);
}

bool dfs(pair<int, int> curr) {
    if (curr == dest) return true;
    visited[curr.first][curr.second] = true;
    for (pair<int, int> i : mv)
        if (good(curr.X + i.X, curr.Y + i.Y) && dfs({curr.X + i.X, curr.Y + i.Y}))
            return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(v, 0x3f, sizeof v);
    cin >> n >> m >> src.X >> src.Y >> dest.X >> dest.Y >> k;
    while (k--) {
        int x, y;
        cin >> x >> y;
        v[x][y] = 0;
    }
    FOR(i, 1, n + 1) FOR(j, 1, m + 1)
        v[i][j] = min(v[i][j], v[i - 1][j] + 1),
        v[n - i + 1][j] = min(v[n - i + 1][j], v[n - i + 2][j] + 1);
    
    FOR(i, 1, n + 1) {
        l = r = 0;
        FOR(j, 1, m + 1) {
            dp[i][j] = sq(v[i][j]);
            while (r - l > 1 && case_1(dq[l], dq[l + 1], j, i)) l++;
            if (r - l) dp[i][j] = min(dp[i][j], sq(j - dq[l]) + sq(v[i][dq[l]]));
            while (r - l > 1 && case_2(dq[r - 2], dq[r - 1], j, i)) r--;
            if (v[i][j] < n) dq[r++] = j;
        }
        reverse(v[i] + 1, v[i] + m + 1);
        reverse(dp[i] + 1, dp[i] + m + 1);
        l = r = 0;
        FOR(j, 1, m + 1) {
            while (r - l > 1 && case_1(dq[l], dq[l + 1], j, i)) l++;
            if (r - l) dp[i][j] = min(dp[i][j], sq(j - dq[l]) + sq(v[i][dq[l]]));
            while (r - l > 1 && case_2(dq[r - 2], dq[r - 1], j, i)) r--;
            if (v[i][j] < n) dq[r++] = j;
        }
    }

    src.Y = m + 1 - src.Y;
    dest.Y = m + 1 - dest.Y;

    l = 0, r = dp[src.X][src.Y];
    while (l != r) {
        mid = (l + r + 1) >> 1;
        memset(visited, 0, sizeof visited);
        if (dfs(src)) l = mid;
        else r = mid - 1;
    }
    cout << l;
    return 0;
}