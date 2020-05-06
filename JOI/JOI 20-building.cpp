/*
JOI 2020 Building
- Let dp[i][j][k] = True iff we can have j type-1 buildings in the first i spots and the i-th building is k
- If we brute force a bunch of small cases, we notice that for each i and k, the j's where dp[i][j][k] = True
  form a contiguous interval
- This means we just have to store the start and endpoints of each interval and drop the second dimension
- Constructing the answer just requires greedily taking type-0 buildings until you can't anymore
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[1000001], b[1000001];
pair<int, int> dp[1000001][2];

void update(pair<int, int> &X, pair<int, int> &Y) {
    X.first = min(X.first, Y.first);
    X.second = max(X.second, Y.second);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, 2 * n + 1) cin >> a[i];
    FOR(i, 1, 2 * n + 1) cin >> b[i];
    dp[0][0] = dp[0][1] = {0, 0};
    FOR(i, 1, 2 * n + 1) {
        dp[i][0] = dp[i][1] = {n + 1, -n - 1};
        if (a[i] >= a[i - 1]) update(dp[i][0], dp[i - 1][0]);
        if (a[i] >= b[i - 1]) update(dp[i][0], dp[i - 1][1]);
        if (b[i] >= a[i - 1]) update(dp[i][1], dp[i - 1][0]);
        if (b[i] >= b[i - 1]) update(dp[i][1], dp[i - 1][1]);
        dp[i][1].first++, dp[i][1].second++;
    }

    string ans = "";
    for (int i = 2 * n, curr = INT_MAX; i; i--) {
        if (a[i] > curr || dp[i][0].first > n || dp[i][0].second < n) {
            if (b[i] > curr || dp[i][1].first > n || dp[i][1].second < n) return cout << -1, 0;
            ans += "B", curr = b[i], n--;
        } else ans += "A", curr = a[i];
    }
    
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}