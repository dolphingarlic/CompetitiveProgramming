#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
pair<ll, ll> a[500001];
ll v[1000001];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i].first >> a[i].second;
    sort(a, a + n);
	FOR(i, 0, n - 1) {
		v[2 * i] = a[i].second;
		v[2 * i + 1] = a[i].first - a[i + 1].first;
	}
	v[2 * n - 2] = a[n - 1].second;
 
	ll gm = 0, lm = 0;
	FOR(i, 0, 2 * n - 1) {
		lm = max(lm + v[i], v[i]);
		gm = max(gm, lm);
	}
	cout << gm << '\n';
    return 0;
}