#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll diffs[200001];
ll n, q, s, t, wind = 0;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q >> s >> t;
    ll curr;
    cin >> curr;
    FOR(i, 1, n + 1) {
        ll x;
        cin >> x;
        diffs[i] = x - curr;
        curr = x;
    }
    FOR(i, 1, n + 1) {
        if (diffs[i] > 0)
            wind -= diffs[i] * s;
        else
            wind -= diffs[i] * t;
    }
 
    FOR(i, 0, q) {
        ll a, b, x;
        cin >> a >> b >> x;
        if (diffs[a] > 0)
            wind += diffs[a] * s;
        else
            wind += diffs[a] * t;
        if (b != n) {
            if (diffs[b + 1] > 0)
                wind += diffs[b + 1] * s;
            else
                wind += diffs[b + 1] * t;
        }
 
        diffs[a] += x;
        diffs[b + 1] -= x;
 
        if (diffs[a] > 0)
            wind -= diffs[a] * s;
        else
            wind -= diffs[a] * t;
        if (b != n) {
            if (diffs[b + 1] > 0)
                wind -= diffs[b + 1] * s;
            else
                wind -= diffs[b + 1] * t;
        }
 
        cout << wind << '\n';
    }
    return 0;
}