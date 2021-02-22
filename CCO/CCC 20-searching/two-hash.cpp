#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll P1 = 9973, P2 = 69420, M1 = 1e9 + 9, M2 = 998244353;

ll inv(ll base, ll MOD) {
    ll ans = 1, expo = MOD - 2;
    while (expo) {
        if (expo & 1) ans = ans * base % MOD;
        expo >>= 1;
        base = base * base % MOD;
    }
    return ans;
}

string n, h;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> h;
    if (n.size() > h.size()) return cout << 0, 0;

    set<pair<ll, ll>> good;
    ll n_hsh1 = 1, h_hsh1 = 1, n_hsh2 = 1, h_hsh2 = 1;
    ll poly1 = 0, poly2 = 0, p_pow1 = 1, p_pow2 = 1;
    for (int i = 0; i < n.size(); i++) {
        n_hsh1 = n_hsh1 * (P1 + n[i] - 'a') % M1;
        n_hsh2 = n_hsh2 * (P2 + n[i] - 'a') % M2;
        h_hsh1 = h_hsh1 * (P1 + h[i] - 'a') % M1;
        h_hsh2 = h_hsh2 * (P2 + h[i] - 'a') % M2;

        poly1 = (poly1 * P1 + (h[i] - 'a')) % M1;
        poly2 = (poly2 * P2 + (h[i] - 'a')) % M2;
        p_pow1 = p_pow1 * P1 % M1;
        p_pow2 = p_pow2 * P2 % M2;
    }
    if (n_hsh1 == h_hsh1 && n_hsh2 == h_hsh2) good.insert({poly1, poly2});

    for (int i = n.size(); i < h.size(); i++) {
        h_hsh1 = h_hsh1 * inv(P1 + h[i - n.size()] - 'a', M1) % M1 * (P1 + h[i] - 'a') % M1;
        h_hsh2 = h_hsh2 * inv(P2 + h[i - n.size()] - 'a', M2) % M2 * (P2 + h[i] - 'a') % M2;

        poly1 = (poly1 * P1 - p_pow1 * (h[i - n.size()] - 'a') % M1 + (h[i] - 'a') + M1) % M1;
        poly2 = (poly2 * P2 - p_pow2 * (h[i - n.size()] - 'a') % M2 + (h[i] - 'a') + M2) % M2;
        
        if (n_hsh1 == h_hsh1 && n_hsh2 == h_hsh2) good.insert({poly1, poly2});
    }

    cout << good.size() << '\n';
    return 0;
}
