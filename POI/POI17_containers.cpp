#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

const int k = 300;
int containers[100001];
int dp[100001 + k][k];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    while (q--) {
        int a, l, d;
        cin >> a >> l >> d;
        if (d >= k) FOR(i, 0, l) containers[a + i * d]++;
        else {
            dp[a][d]++;
            dp[a + (l * d)][d]--;
        }
    }

    FOR(j, 1, k) FOR(i, j, n + 1) dp[i][j] += dp[i - j][j];

    FOR(i, 1, n + 1) {
        FOR(j, 1, k) containers[i] += dp[i][j];
        cout << containers[i] << ' ';
    }
    return 0;
}