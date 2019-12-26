#include <bits/stdc++.h>
using namespace std;

long long dp[20][2][2][11][11];
vector<int> num;
int n;

long long solve(int i, int sm, int lz, int prev1, int prev2) {
    if (i == n) {
        return !lz;
    }
    if (dp[i][sm][lz][prev1][prev2] != -1) {
        return dp[i][sm][lz][prev1][prev2];
    }
    long long ans = 0;
    int mx;
    if (sm) {
        mx = num[i];
    } else {
        mx = 9;
    }
    for (int d = 0; d <= mx; d++) {
        if (d == prev1 || d == prev2) {
            continue;
        }
        if (lz && d == 0) {
            ans += solve(i + 1, (sm && d == num[i]), 1, 10, 10);
        } else {
            ans += solve(i + 1, (sm && d == num[i]), 0, prev2, d);
        }
    }
    return (dp[i][sm][lz][prev1][prev2] = ans);
}

long long calc(long long x) {
    num.clear();
    while (x > 0) {
        num.push_back(x % 10);
        x /= 10;
    }
    reverse(num.begin(), num.end());
    n = (int)num.size();
    memset(dp, -1, sizeof dp);
    return solve(0, 1, 1, 10, 10);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long a, b;
    cin >> a >> b;
    long long ans = calc(b);
    if (a > 1) {
        ans -= calc(a - 1);
    }
    if (a == 0) {
        ans++;
    }
    cout << ans << '\n';
    return 0;
}