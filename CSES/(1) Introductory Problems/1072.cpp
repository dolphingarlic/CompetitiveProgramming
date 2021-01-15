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
    FOR(i, 1, n + 1) {
        cout << ((i - 1) * (i + 4) * (i * i - 3 * i + 4)) / 2 << '\n';
    }
    return 0;
}