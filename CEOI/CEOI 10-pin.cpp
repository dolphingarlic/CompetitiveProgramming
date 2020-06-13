/*
CEOI 2010 Pin
- Since the lengths of the strings are short, we can find how many
  pairs differ in at most K positions for K from 0 to 4
    - We can hash the strings minus the positions they differ in
      and insert them into a map to do this
- Then we use PIE to count the answer for each D
- Complexity: O(16N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

map<string, ll> cnt[16];
ll ans[5];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, d;
    cin >> n >> d;
    FOR(i, 0, n) {
        string s;
        cin >> s;
        FOR(j, 0, 16) {
            string sub = "";
            FOR(k, 0, 4) if (j & (1 << k)) sub += s[k];
            cnt[j][sub]++;
        }
    }

    FOR(i, 0, 16) {
        ll contrib = 0;
        for (pair<string, ll> j : cnt[i])
            contrib += j.second * (j.second - 1) / 2;
        ans[4 - __builtin_popcount(i)] += contrib;
    }
    
    if (d == 1) cout << ans[1] - ans[0];
    else if (d == 2) cout << ans[2] - 3 * (ans[1] - ans[0]);
    else if (d == 3) cout << ans[3] - 2 * ans[2] + 3 * (ans[1] - ans[0]);
    else cout << ans[4] - ans[3] + ans[2] - ans[1] + ans[0];
    return 0;
}