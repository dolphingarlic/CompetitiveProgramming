/*
Balkan 2019 Fishermen
- It's optimal to make all fishermen either happy or angry by supporting
  his rivals
    - If you make a fisherman angry, you may as well support all of his rivals
- Each fisherman corresponds to an interval and we want to cover all fishermen
  using as few intervals as possible
- This just becomes POI 2014 Around the World
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, nxt[1000000];
ll r, t, x[2000000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> r >> t;
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) {
        x[n + i] = x[i] + t;
        nxt[i] = upper_bound(x + i, x + n + i,
                    *prev(upper_bound(x + i, x + n + i, x[i] + r)) + r) - x;
        if (nxt[i] >= n) nxt[i] -= n;
    }
    int curr = 0;
    for (int i = 0; i < n; i++) curr = nxt[curr];
    int ans = n;
    for (int i = curr, loop_cnt = 0; loop_cnt + (i >= curr) < 2; ans--) {
        if (nxt[i] <= i) loop_cnt++;
        i = nxt[i];
    }
    cout << ans;
    return 0;
}