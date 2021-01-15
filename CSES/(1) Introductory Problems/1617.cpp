#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
ll expo(ll base, int n) {
    ll ans = 1;
    while (n) {
        if (n & 1) ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        n >>= 1;
    }
    return ans;
}
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    cout << expo(2, n);
    return 0;
}