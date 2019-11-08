#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Wall {
    ll h, a, b;
};
bool operator<(Wall x, Wall y) {
    return x.h < y.h;
}

vector<Wall> walls;

const ll MOD = 1e9 + 7;

ll cmp[500000], dp[500000], lh[500000];
ll find(ll a) {
    while (a != cmp[a]) cmp[a] = cmp[cmp[a]], a = cmp[a];
    return a;
}
void onion(ll a, ll b, ll h) {
    if (find(a) != find(b)) {
        dp[find(a)] = ((dp[find(a)] + h - lh[find(a)]) * (dp[find(b)] + h - lh[find(b)])) % MOD;
        lh[find(a)] = h;
        cmp[find(b)] = cmp[find(a)];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, h;
    cin >> n >> m >> h;
    FOR(i, 0, n) {
        FOR(j, 0, m - 1) {
            ll x;
            cin >> x;
            walls.push_back({x, i * m + j, i * m + j + 1});
        }
    }
    FOR(i, 0, n - 1) {
        FOR(j, 0, m) {
            ll x;
            cin >> x;
            walls.push_back({x, i * m + j, (i + 1) * m + j});
        }
    }

    FOR(i, 0, n * m) cmp[i] = i, lh[i] = -1;
    sort(walls.begin(), walls.end());
    for (Wall i : walls) onion(i.a, i.b, i.h);

    cout << (dp[find(0)] + h - lh[find(0)]) % MOD;
    return 0;
}