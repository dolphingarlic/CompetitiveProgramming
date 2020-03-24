#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

map<int, int> x, y;
pair<int, int> s[300001];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        cin >> s[i].first >> s[i].second;
        x[s[i].first]++;
        y[s[i].second]++;
    }

    ll ans = 0;
    FOR(i, 0, n) {
        ans += (x[s[i].first] - 1) * (y[s[i].second] - 1);
    }

    cout << ans;
    return 0;
}