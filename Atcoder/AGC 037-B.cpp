#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 998244353;

ll cnt[3];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string s;
    cin >> n >> s;
    ll ans = 1;
    for (int i = 1; i <= n; i++) ans = ans * i % MOD;
    for (char c : s) {
        ll nxt = INT_MAX;
        if (c == 'R') {
            if (cnt[1] > cnt[0]) nxt = min(nxt, cnt[1]);
            if (cnt[2] > cnt[0]) nxt = min(nxt, cnt[2]);
            if (nxt == INT_MAX) nxt = cnt[0] + 1;
            ans = ans * (nxt - cnt[0]) % MOD;
            cnt[0]++;
        } else if (c == 'G') {
            if (cnt[0] > cnt[1]) nxt = min(nxt, cnt[0]);
            if (cnt[2] > cnt[1]) nxt = min(nxt, cnt[2]);
            if (nxt == INT_MAX) nxt = cnt[1] + 1;
            ans = ans * (nxt - cnt[1]) % MOD;
            cnt[1]++;
        } else {
            if (cnt[0] > cnt[2]) nxt = min(nxt, cnt[0]);
            if (cnt[1] > cnt[2]) nxt = min(nxt, cnt[1]);
            if (nxt == INT_MAX) nxt = cnt[2] + 1;
            ans = ans * (nxt - cnt[2]) % MOD;
            cnt[2]++;
        }
    }
    cout << ans;
    return 0;
}
