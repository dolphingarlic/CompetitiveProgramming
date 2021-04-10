#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 998244353;

ll inv(ll base) {
    ll ans = 1, pow = MOD - 2;
    while (pow) {
        if (pow & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        pow >>= 1;
    }
    return ans;
}

ll fact[300001];

ll choose(ll n, ll m) {
    return fact[n] * inv(fact[m]) % MOD * inv(fact[n - m]) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    ll a, b, k;
    cin >> n >> a >> b >> k;

    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;

    ll ans = 0;
    for (ll a_cnt = 0; a_cnt <= n && a * a_cnt <= k; a_cnt++) {
        ll b_sum = k - a * a_cnt;
        ll b_cnt = b_sum / b;
        if (b_sum % b != 0 || b_cnt > n) continue;
        ans = (ans + choose(n, a_cnt) * choose(n, b_cnt)) % MOD;
    }
    cout << ans;
    return 0;
}
