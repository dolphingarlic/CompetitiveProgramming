#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int dp[20000003], p[100001], max_divide[20000003], to[20000003];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    FOR(i, 0, n) cin >> p[i];
    FOR(i, 0, n) for (int j = p[i]; j <= 20000001; j += p[i]) max_divide[j] = p[i];

    int mn = 20000000;
    for (int i = 20000000; i > 0; i--) {
        mn = min(mn, i + 1 - max_divide[i + 1]);
        to[i] = mn;
    }

    FOR(i, 1, 20000001) if (to[i] == i) dp[i] = 987654321;
    else dp[i] = dp[to[i]] + 1;

    FOR(i, 0, q) {
        int x;
        cin >> x;
        if (dp[x] >= 987654321)
            cout << "oo\n";
        else
            cout << dp[x] << '\n';
    }
    return 0;
}