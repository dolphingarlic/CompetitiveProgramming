/*
JOISC 2019 Cake 3
- Sort the cakes by colour
- Ans = max(max(2C[j] + (M best cakes in [j, i])) - 2C[i])
- The optimal j for each i is non-decreasing, so we can use D&C DP to solve this
- We can walk down a segment tree to find (M best cakes in [j, i])
- Complexity: O(N log^2 N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

int n, m;
pair<ll, ll> cake[200001];
ll dp[200001];

void solve(int l, int r, int lopt, int ropt) {
    if (l > r) return;

    int mid = (l + r) / 2;
    int opt = -1;

    // Do stuff

    dp[mid] = -INF;
    for (int i = min(mid - m + 1, ropt); i >= lopt; i--) {
        ll pot = 2 * cake[i].second + m_best();
        if (pot > dp[mid])
            dp[mid] = pot, opt = i;
        toggle_cake(i, true);
    }
    dp[mid] -= 2 * cake[mid].second;

    // Toggle the other cakes

    solve(l, mid - 1, lopt, opt);
    solve(mid + 1, r, opt, ropt);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> cake[i].first >> cake[i].second;
    solve(m, n, 1, n - m + 1);
    cout << *max_element(dp + m, dp + n + 1);
    return 0;
}
