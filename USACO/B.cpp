#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

ll expo(ll base, ll pw) {
    ll ans = 1;
    while (pw) {
        if (pw & 1) ans = F.reduce(ans * base);
        base = F.reduce(base * base);
        pw >>= 1;
    }
    return ans;
}

ll gcd(ll x, ll y) { return (y ? gcd(y, x % y) : x); }
ll lcm(ll x, ll y) { return x * y / gcd(x, y); }

unordered_map<ll, ll> dp[7501];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // ifstream cin("exercise.in");
    // ofstream cout("exercise.out");

    ll n, m;
    cin >> n >> m;
    F = FastMod(m - 1);

    dp[0][1] = 1;
    FOR(i, 1, n + 1) {
        ll fac = 1;
        FOR(j, 1, i + 1) {
            for (auto& k : dp[i - j]) dp[i][lcm(k.first, j)] = F.reduce(dp[i][lcm(k.first, j)] + fac * k.second);
            fac = F.reduce(fac * (i - j));
        }
    }

    ll ans = 1;
    F = FastMod(m);
    for (auto& k : dp[n]) ans = F.reduce(ans * expo(k.first, k.second));
    cout << ans << '\n';
    return 0;
}