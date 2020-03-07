#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll expo(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

int n, m;
ll p[100001], x[100001];
ll bs[400001], pw[400001];

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) {
        bs[node] = expo(p[l], x[l]);
        pw[node] = 2 * x[l] + 1;
    } else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        bs[node] = (bs[node * 2] * bs[node * 2 + 1]) % MOD;
        pw[node] = (pw[node * 2] * pw[node * 2 + 1]) % (MOD - 1);
    }
}

ll q_bs(int a, int b, int node = 1, int l = 1, int r = n) {
    if (l > b || r < a) return 1;
    if (l >= a && r <= b) return bs[node];
    int mid = (l + r) / 2;
    return (q_bs(a, b, node * 2, l, mid) * q_bs(a, b, node * 2 + 1, mid + 1, r)) % MOD;
}

ll q_pw(int a, int b, int node = 1, int l = 1, int r = n) {
    if (l > b || r < a) return 1;
    if (l >= a && r <= b) return pw[node];
    int mid = (l + r) / 2;
    return (q_pw(a, b, node * 2, l, mid) * q_pw(a, b, node * 2 + 1, mid + 1, r)) % (MOD - 1);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) cin >> p[i] >> x[i];
    build();
    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << expo(q_bs(a, b), q_pw(a, b)) << '\n';
    }
    return 0;
}