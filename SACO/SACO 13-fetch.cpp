/*
SACO 2013 Fetching Rum
- Binary search for the answer: if we can achieve x, then we can also achieve x - k
- Let the current candidate be max_wait
- dp[i] = min(max(a[i], dp[j] + m) : max(a[i], dp[j] + m) <= a[j + 1] + max_wait)
    - If there are no j's satisfying the condition, then max_wait can't be achieved
- Since dp is monotone and m and max_wait are fixed, we can just use two pointers
  to calculate dp in O(N)
- Complexity: O(N log M)
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, a[100001], dp[100001];

bool check(int max_wait) {
    memset(dp, 0x3f, sizeof dp);
    dp[0] = -m;
    for (int rptr = 1, lptr = 0; rptr <= n; rptr++) {
        while (lptr < rptr && max(a[rptr], dp[lptr] + m) > a[lptr + 1] + max_wait)
            lptr++;
        if (max(a[rptr], dp[lptr] + m) > a[lptr + 1] + max_wait)
            return false;
        dp[rptr] = max(a[rptr], dp[lptr] + m);
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    a[0] = -m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int l = 0, r = m;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}