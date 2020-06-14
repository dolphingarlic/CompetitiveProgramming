/*
CEOI 2010 Tower
- First, sort the array
- Assume we have an infinitely large block in the array which acts as the base
- Let dp[i] be the number of ways to make the tower with the first i blocks
    - Notice how we can place any block on top of block i
    - This means dp[i] = dp[i - 1] * cnt, where
      cnt = Number of blocks on which we can place block i
    - To find cnt, we can use 2 pointers
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    FOR(i, 0, n) cin >> a[i];
    sort(a.begin(), a.end());

    ll ans = 1;
    int ptr = 0;
    FOR(i, 0, n) {
        while (a[i] - a[ptr] > d) ptr++;
        ans = (ans * (i - ptr + 1)) % MOD;
    }
    cout << ans;
    return 0;
}