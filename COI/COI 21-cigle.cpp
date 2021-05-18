#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[5001], pref[5001], dp[5001][5001];
bool visited[5001][5001];

void compute(int l, int r) {
    if (visited[l][r]) return;
    visited[l][r] = true;

    int cnt = 0, curr_sm = 0;
    for (int i = l - 1, j = l; i; i--) {
        while (pref[l - 1] - pref[i - 1] > curr_sm && j <= r)
            curr_sm += a[j++];
        compute(i, l - 1);
        dp[l][r] = max(dp[l][r], dp[i][l - 1] + cnt);
        if (pref[l - 1] - pref[i - 1] == curr_sm && j <= r) cnt++;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = a[i] + pref[i - 1];
    }

    for (int i = 1; i <= n; i++) visited[1][i] = true;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        compute(i, n);
        ans = max(ans, dp[i][n]);
    }
    cout << ans;
    return 0;
}
