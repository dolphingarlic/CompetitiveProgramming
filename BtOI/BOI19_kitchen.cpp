#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int dp[90001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k, sm = 0;
    cin >> n >> m >> k;
    if (m < k) return cout << "Impossible", 0;
    FOR(i, 0, n) {
        int a;
        cin >> a;
        if (a < k) return cout << "Impossible", 0;
        sm += a;
    }

    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    FOR(i, 1, m + 1) {
        int x;
        cin >> x;
        for (int j = 90000 - x; ~j; j--) if (~dp[j]) {
            dp[j + x] = max(dp[j + x], dp[j] + min(x, n));
        }
    }

    FOR(i, sm, 90001) if (dp[i] >= n * k) return cout << i - sm, 0;
    cout << "Impossible";
    return 0;
}