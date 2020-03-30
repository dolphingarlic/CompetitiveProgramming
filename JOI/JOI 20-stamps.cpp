/*
JOI 2020 Collection Stamps
- dp[i][j][k][l] = Min time if visited range = [i, j] with k stamps collected. l = Currently at i
- Complexity: O(N^3)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

const int INF = 1e9;

inline void mn(int &A, int B) { A = min(A, B); }

int a[401], t[401], dp[401][401][401][2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, p;
    cin >> n >> p;
    FOR(i, 0, n) {
        cin >> a[i];
        a[i + n + 1] = a[i];
    }
    FOR(i, 0, n) {
        cin >> t[i];
        t[i + n + 1] = t[i];
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[n][n][0][0] = 0;
    int ans = 0;
    FOR(range, 0, n + 1) FOR(i, n - range, n + 1) FOR(k, 0, range + 1) FOR(l, 0, 2) {
        int j = i + range, curr = (l ? i : j);
        if (dp[i][j][k][l] > INF) continue;
        
        if (j < 2 * n - 1) {
            int dist = min(p - abs(a[curr] - a[j + 1]), abs(a[curr] - a[j + 1])) + dp[i][j][k][l];
            mn(dp[i][j + 1][k + (dist <= t[j + 1])][0], dist);
        }

        if (i) {
            int dist = min(p - abs(a[curr] - a[i - 1]), abs(a[curr] - a[i - 1])) + dp[i][j][k][l];
            mn(dp[i - 1][j][k + (dist <= t[i - 1])][1], dist);
        }
        ans = max(ans, k);
    }
    cout << ans;
    return 0;
}