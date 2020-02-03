#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll pw[1000001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    string s;
    cin >> n >> m >> s;

    pw[0] = 1;
    FOR(i, 1, n + 1) pw[i] = (2 * pw[i - 1]) % m;
    
    ll ans = 1;
    int mn = 0, mx = 0, curr = 0;
    FOR(i, 0, n) {
        if (s[i] == 'L') mx = max(mx, ++curr);
        else {
            int temp_mx = max(mx, curr + 1);
            int k = n - i - 1;

            if (temp_mx - mn == 2) {
                if (curr + 1 == temp_mx - 1) ans = (ans + pw[(k + 1) / 2]) % m;
                else ans = (ans + pw[k / 2]) % m;
            } else if (temp_mx - mn == 1) ans = (ans + pw[k / 2] + pw[(k + 1) / 2] - 1) % m;

            mn = min(mn, --curr);
        }
    }

    cout << ans;
    return 0;
}