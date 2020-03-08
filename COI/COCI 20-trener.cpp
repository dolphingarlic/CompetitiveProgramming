/*
COCI 2020 Trener
- Notice that we only need to check consecutive words and that only the first and last
  letters can differ
- We just use a map and some dp to solve this
- Complexity: O(NK^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
const ll M = 1e9 + 7;

ll dp[1501];

map<string, ll> mp;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 1, n + 1) FOR(j, 1, k + 1) {
        string s;
        cin >> s;
        dp[j] = (i > 1 ? mp[s.substr(0, i - 1)] + mp[s.substr(1, i - 1)] : 1);
        if (i > 1 && s.substr(0, i - 1) == s.substr(1, i - 1)) dp[j] -= mp[s.substr(1, i - 1)];
        if (dp[j] >= M) dp[j] -= M;
        mp[s] += dp[j];
        if (mp[s] >= M) mp[s] -= M;
    }
    ll ans = 0;
    FOR(i, 1, k + 1) {
        ans += dp[i];
        if (ans >= M) ans -= M;
    }
    cout << ans;
    return 0;
}