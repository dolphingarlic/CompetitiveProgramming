/*
SACO 2012 Visiting Neighbours
- Just do it
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int ans[1000000];
unordered_map<ll, int> mp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(ans, 0x3f, sizeof ans);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        ll h;
        cin >> h;
        if (mp[h]) {
            ans[i] = min(ans[i], i - mp[h]);
            ans[mp[h]] = min(ans[mp[h]], i - mp[h]);
        }
        mp[h] = i;
    }
    FOR(i, 1, n + 1) cout << (ans[i] == 0x3f3f3f3f ? -1 : ans[i]) << ' ';
    return 0;
}