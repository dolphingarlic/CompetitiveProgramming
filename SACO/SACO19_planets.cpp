#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return (b ? gcd(b, a % b) : a);
}

int n;
ll t[8], dp[1<<8];
bool visited[8];

vector<ll> lcms[8];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> t[i];

    dp[0] = 1;
    FOR(i, 1, (1<<n)) {
        int bitcnt = 0;
        for (int j = 0; j < n; j++) if (i & (1 << j)) {
            bitcnt++;
            dp[i] = t[j] * dp[i - (1 << j)] / gcd(t[j], dp[i - (1 << j)]);
        }
        lcms[bitcnt - 1].push_back(dp[i]);
    }

    ll l = 1, r = LLONG_MAX - 1;
    while (l != r) {
        ll mid = (l + r) / 2;
        ll num = 0;
        FOR(i, 0, n) for (ll j : lcms[i]) num += mid / (i & 1 ? -j : j);
        if (num >= k) r = mid;
        else l = mid + 1;
    }

    cout << 2020 + l;
    return 0;
}