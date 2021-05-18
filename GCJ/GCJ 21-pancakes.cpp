#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll fact[100001];

ll expo(ll base, ll pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        pow >>= 1;
    }
    return ans;
}

ll choose(int t, int m) {
    if (m > t || m < 0) return 0;
    return fact[t] * expo(fact[m], MOD - 2) % MOD * expo(fact[t - m], MOD - 2) % MOD;
}

int n, v[100001];
pair<int, int> segtree[400001];

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) segtree[node] = {v[l], -l};
    else {
        int mid = (l + r) / 2;
        segtree[node * 2] = segtree[node * 2 + 1] = {INT_MAX, INT_MAX};
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

pair<int, int> query(int a, int b, int node = 1, int l = 1, int r = n) {
    if (l >= a && r <= b) return segtree[node];
    if (l > b || r < a) return {INT_MAX, INT_MAX};
    int mid = (l + r) / 2;
    return min(query(a, b, node * 2, l, mid), query(a, b, node * 2 + 1, mid + 1, r));
}

ll solve(int l = 1, int r = n) {
    if (r <= l) return 1;
    int mx_pos = -query(l, r).second;
    return choose(r - l, mx_pos - l) * solve(l, mx_pos - 1) % MOD * solve(mx_pos + 1, r) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    fact[0] = 1;
    for (int i = 1; i <= 100000; i++)
        fact[i] = fact[i - 1] * i % MOD;
    int t;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        cin >> n;
        bool good = true;
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
            if (v[i] > v[i - 1] && v[i] - v[i - 1] != 1)
                good = false;
        }
        if (!good) {
            cout << "Case #" << test << ": 0\n";
        } else {
            build();
            cout << "Case #" << test << ": " << solve() << '\n';
        }
    }
    return 0;
}
