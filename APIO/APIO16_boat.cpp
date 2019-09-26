#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll expo(ll base, ll pow) {
    ll res = 1;
    while (pow) {
        if (pow & 1) res = (res * base) % MOD;
        pow >>= 1;
        base = (base * base) % MOD;
    }
    return res;
}

pair<int, int> a[501];
set<int> segments;
vector<int> b;
ll dp[501][1001], c[501][1001];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> a[i].first >> a[i].second;
        segments.insert(a[i].first);
        segments.insert(a[i].second);
    }
    for (int i : segments) b.push_back(i);

    FOR(i, 1, b.size()) {
        c[i][0] = 1;
        FOR(j, 1, b[i] - b[i - 1] + 1) {
            c[i][j] =
                ((c[i][j - 1] * (b[i] - b[i - 1] - j + 1)) % MOD * expo(j, MOD - 2)) % MOD;
            
            cout << i << ' ' << j << ' ' << c[i][j] << '\n';
        }
    }
    cout << '\n';

    FOR(i, 0, b.size()) dp[0][i] = 1;
    FOR(i, 1, b.size()) {
        dp[0][i] = 1;
        FOR(j, 1, n + 1) {
            int k = 1;
            dp[j][i] = dp[j - 1][i];
            while (k <= b[i] - b[i - 1] && a[j - k + 1].second >= b[i] &&
                   a[j - k + 1].first <= b[i - 1]) {
                dp[j][i] = (dp[j][i] + dp[j - k][i - 1] * c[i][k]) % MOD;
                k++;
            }

            cout << i << ' ' << j << ' ' << dp[j][i] << '\n';
        }
    }

    cout << dp[n][b.size() - 1];
    return 0;
}