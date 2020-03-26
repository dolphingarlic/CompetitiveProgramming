/*
NOI 2018 Safety
- Let dp[i][j] = Minimum cost to make the first i blocks safe where block i has height j
- dp[1][j] = abs(j - a[1])
- dp[i][j] = abs(j - a[i]) + min(dp[i - 1][k]) for j - h <= k <= j + h
- For each i, if we plot dp[i][j] against j, we notice that the graph is convex
    - Convince yourself that this is true because I'm not proving this
- This implies that we should use slope trick
- Notice that if we have dp[i - 1] and we process block i...
    - First, we move each point h units away from the minimum
    - Next, we add an absolute value graph on top of it
- Just use slope trick
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[200001];
priority_queue<ll> L, R;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll h;
    cin >> n >> h;
    FOR(i, 0, n) cin >> a[i];

    ll ans = 0;
    L.push(a[0]); R.push(-a[0]);
    FOR(i, 1, n) {
        ll X = L.top() - h * i, Y = -R.top() + h * i;
        if (X > a[i]) {
            ans += X - a[i];
            L.push(a[i] + h * i);
            L.push(a[i] + h * i);
            R.push(-X + h * i);
            L.pop();
        } else if (Y < a[i]) {
            ans += a[i] - Y;
            R.push(-a[i] + h * i);
            R.push(-a[i] + h * i);
            L.push(Y + h * i);
            R.pop();
        } else {
            L.push(a[i] + h * i);
            R.push(-a[i] + h * i);
        }
    }
    cout << ans;
    return 0;
}