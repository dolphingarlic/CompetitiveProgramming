/*
JOI 2015 Railway
- For each rail, find how many times it's traversed
    - We do this with a line sweeep
- Then for each rail, ans += min(used * A, used * B + C)
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int q[100001], cnt = 0, ptr = 0;
vector<pair<int, int>> sweep;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        cin >> q[i];
        if (i) {
            sweep.push_back({min(q[i], q[i - 1]), 1});
            sweep.push_back({max(q[i], q[i - 1]), -1});
        }
    }
    sort(sweep.begin(), sweep.end());
    ll ans = 0;
    FOR(i, 1, n) {
        while (ptr < sweep.size() && sweep[ptr].first <= i) cnt += sweep[ptr++].second;
        ll a, b, c;
        cin >> a >> b >> c;
        ans += min(cnt * a, cnt * b + c);
    }
    cout << ans << '\n';
    return 0;
}