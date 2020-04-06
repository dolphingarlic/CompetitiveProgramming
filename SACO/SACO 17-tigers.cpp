#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MAXN 100001
#define MOD 1000000007ll
typedef long long ll;
using namespace std;

ll bit[MAXN];                   // s is sorted list of x positions
pair<ll, ll> a[MAXN], s[MAXN];  // Height then x position
ll n, k;

// Range updates using prefix sums
void updateBIT(ll index, ll val) {
    for (ll i = index + 1; i <= n; i += (i & (-i)))
        bit[i] = (bit[i] + val + MOD) % MOD;
}

void update(ll k, ll r, ll val) {
    val = (val + MOD) % MOD;
    updateBIT(k, val);
    updateBIT(r + 1, -val);
}

// Point queries
ll query(ll index) {
    ll sum = 0;
    for (ll i = index + 1; i > 0; i -= (i & (-i)))
        sum = (sum + bit[i] + MOD) % MOD;
    return sum;
}

ll find(ll second, ll first) {
    ll l = 0, r = n - 1;
    while (l != r) {
        ll mid = (l + r) / 2;
        if (s[mid].first < second ||
            (s[mid].first == second && s[mid].second < first))
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    FOR(i, 0, n) {
        cin >> a[i].second >> a[i].first;
        s[i] = {a[i].second, a[i].first};
    }
    sort(a, a + n, greater<pair<ll, ll>>());
    sort(s, s + n);

    // 1 way to go from the highest ledge to the ground
    update(find(a[0].second, a[0].first), find(a[0].second, a[0].first), 1);
    // Total number of ways
    ll tot = 0;
    for (ll i = 0; i < n;) {
        // Handle cases where heights are the same
        vector<ll> u;
        vector<pair<ll, ll>> v;
        ll h = a[i].first;
        do {
            ll pos = find(a[i].second, a[i].first);
            // Add number of ways to get to the current ledge to the total
            u.push_back(query(pos));
            tot = (tot + u.back() + MOD) % MOD;
            v.push_back(a[i++]);
        } while (i < n && a[i].first == h);

        // Then update ranges
        FOR(i, 0, v.size()) {
            ll pos = find(v[i].second, v[i].first);
            // Boundaries for range update
            ll l = lower_bound(s, s + n, make_pair(v[i].second - k, 0ll)) - s;
            ll r = upper_bound(s, s + n, make_pair(v[i].second + k, LLONG_MAX)) - s - 1;
            update(l, r, u[i]);
        }
    }
    cout << (tot + MOD) % MOD << '\n';
    return 0;
}