/*
Balkan 2019 Tennis
- Same as https://codeforces.com/gym/102059/problem/M
- Basically do parametric search on a tree
- Complexity: O(N log MAX_ANS)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<ll, int> operator+(pair<ll, int> A, pair<ll, int> B) {
    return {A.first + B.first, A.second + B.second};
}

pair<ll, int> operator-(pair<ll, int> A, pair<ll, int> B) {
    return {A.first - B.first, A.second - B.second};
}

const ll INF = 1e12;

int n, k;
vector<pair<int, int>> graph[1000001];
pair<ll, int> dp[1000001][2];

void dfs(ll lambda, int node = 1, int parent = 0) {
    pair<ll, int> sm = {0, 0};
    for (pair<int, int> i : graph[node]) if (i.first != parent) {
        dfs(lambda, i.first, node);
        sm = sm + max(dp[i.first][0], dp[i.first][1]);
    }
    dp[node][0] = dp[node][1] = sm;
    for (pair<int, int> i : graph[node]) if (i.first != parent) {
        dp[node][1] = max(
            dp[node][1],
            make_pair(i.second + lambda, 1) + sm
                - max(dp[i.first][0], dp[i.first][1]) + dp[i.first][0]
        );
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x].push_back({y, w});
        graph[y].push_back({x, w});
    }

    dfs(INF);
    if (max(dp[1][0], dp[1][1]).second < k)
        return cout << -1, 0;

    ll l = -INF, r = INF;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        dfs(mid);
        if (dp[1][0].second < k && dp[1][1].second < k) l = mid + 1;
        else r = mid;
    }
    ll mid = (l + r) / 2;
    dfs(mid);
    cout << max(dp[1][0], dp[1][1]).first - k * mid;
    return 0;
}