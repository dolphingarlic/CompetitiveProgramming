/*
JOI 2018 Bitaro's Birthday
- Main idea: sqrt decomposition
- If the number of people who can't stand Bitaro and are having fun at a party elsewhere is < sqrt(N), then
  we can just look at the sqrt(N) farthest people from town T
    - The farthest person who tolerates Bitaro must be in that list (if they even exist)
    - It takes O((N + M) * sqrt(N)) time to precompute these lists
    - We can use 2 pointers to speed up merging and get rid of a log factor
- If the number of people who vehemently dislike Bitaro is >= sqrt(N), then we can just do an O(N + M) DAG DP
    - This works because there are at most Q / sqrt(N) of these parties
    - This means it takes O((N + M) * sqrt(N)) time to process all these queries
- Conveniently, the list of towns is already topologically sorted
- Complexity: O((N + M) * sqrt(N))
*/

#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

const int L = 111;

vector<int> graph[100001];
vector<pair<int, int>> sqrt_farthest[100001];
int a[100001], dp[100001];
bool bad[100001], in_ret[100001];

inline vector<pair<int, int>> merge(vector<pair<int, int>> X, vector<pair<int, int>> Y) {
    vector<pair<int, int>> ret;
    int xptr = 0;
    for (int yptr = 0; ret.size() <= L && yptr < Y.size() && xptr < X.size(); yptr++) {
        while (xptr < X.size() && X[xptr].second >= Y[yptr].second) {
            if (!in_ret[X[xptr].first]) ret.push_back({X[xptr].first, X[xptr].second + 1});
            in_ret[X[xptr].first] = true;
            xptr++;
        }
        if (!in_ret[Y[yptr].first]) ret.push_back(Y[yptr]);
        in_ret[Y[yptr].first] = true;
    }
    while (xptr < X.size() && ret.size() <= L) {
        if (!in_ret[X[xptr].first]) ret.push_back({X[xptr].first, X[xptr].second + 1});
        in_ret[X[xptr].first] = true;
        xptr++;
    }
    for (pair<int, int> i : ret) in_ret[i.first] = false;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    FOR(i, 0, m) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    FOR(i, 1, n + 1) sqrt_farthest[i] = {{i, 0}};
    FOR(i, 1, n + 1) for (int j : graph[i]) sqrt_farthest[j] = merge(sqrt_farthest[i], sqrt_farthest[j]);

    while (k--) {
        int t, y;
        cin >> t >> y;
        FOR(i, 0, y) {
            cin >> a[i];
            bad[a[i]] = true;
        }

        if (y >= L) {
            FOR(i, 1, n + 1) dp[i] = (bad[i] ? INT_MIN : 0);
            FOR(i, 1, t + 1) for (int j : graph[i]) dp[j] = max(dp[j], dp[i] + 1);
            cout << max(-1, dp[t]) << '\n';
        } else {
            bool can = false;
            for (pair<int, int> i : sqrt_farthest[t]) if (!bad[i.first]) {
                can = true;
                cout << i.second << '\n';
                break;
            }
            if (!can) cout << "-1\n";
        }

        FOR(i, 0, y) bad[a[i]] = false;
    }
    return 0;
}