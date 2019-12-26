#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll fact(ll x) {
    if (x == 0) return 1;
    return (x * fact(x - 1)) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("svejksis.txt", "r", stdin);
    freopen("svejkval.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;
    if (n & 1) {
        cout << n * (n - 1) / 2 - 1 + n / 2 << ' ' << (4 * (fact((n - 1) / 2) * fact((n - 3) / 2)) % MOD) % MOD << '\n';

        cout << n / 2 << ' ';
        FOR(i, 1, n / 2) cout << n / 2 + i + 1 << ' ' << i << ' ';
        cout << n << ' ' << n / 2 + 1 << '\n';
    } else {
        cout << n * (n - 1) / 2 - 1 + n / 2 << ' ' << (2 * (fact((n - 2) / 2) * fact((n - 2) / 2)) % MOD) % MOD << '\n';

        cout << n / 2 << ' ';
        FOR(i, 1, n / 2) cout << n / 2 + i + 1 << ' ' << i << ' ';
        cout << n / 2 + 1 << '\n';
    }
    return 0;
}