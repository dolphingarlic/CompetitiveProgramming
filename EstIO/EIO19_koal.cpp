#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[36];

vector<pair<ll, ll>> make(int s, int e) {
    int n = e - s;
    vector<pair<ll, ll>> ret;
    FOR(i, 1, (1<<n)) {
        ll sum = 0, least;
        FOR(j, 0, n) if (i & (1<<j)) sum += a[s + j], least = a[s + j];
        ret.push_back({sum, least});
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("koalsis.txt", "r", stdin);
    freopen("koalval.txt", "w", stdout);
    
    ll n;
    int k;
    cin >> n >> k;
    FOR(i, 0, k) cin >> a[i];
    sort(a, a + k, greater<ll>());

    vector<pair<ll, ll>> left = make(0, k / 2);
    vector<pair<ll, ll>> right = make(k / 2, k);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    ll ans = 0;
    for (auto& i : left) if (i.first > n / 2 && i.first - i.second <= n / 2) ans++;
    for (auto& i : right) {
        if (i.first > n / 2 && i.first - i.second <= n / 2) ans++;
        // Binsearch for other i.e. MITM
        ans += max(0ll, (ll)(upper_bound(left.begin(), left.end(), make_pair(n / 2 - i.first + i.second, LLONG_MAX)) - upper_bound(left.begin(), left.end(), make_pair(n / 2 - i.first, LLONG_MAX))));
    }

    cout << ans;
    return 0;
}