#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(ll i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    ll curr = 0, tot = 0;
    FOR(i, 0, n) {
        ll x;
        cin >> x;
        if (x < curr) tot += (curr - x);
        curr = max(curr, x);
    }
    cout << tot << '\n';
    return 0;
}