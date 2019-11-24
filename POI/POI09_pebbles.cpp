#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[1000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n >> a[0];
        int xr = (n & 1 ? a[0] : 0);
        FOR(i, 1, n) {
            cin >> a[i];
            if ((n - i) & 1) xr ^= a[i] - a[i - 1];
        }
        if (xr) cout << "TAK\n";
        else cout << "NIE\n";
    }
    return 0;
}