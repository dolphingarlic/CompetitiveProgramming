/*
JOI 2021 Photo
- Notice how the "sorted" sequence will always be of the form
    {x1, x1 - 1, x1 - 2, ..., 1, x2, x2 - 1, x2 - 2, ..., x1 + 1, ...}
- We can thus define dp[i] as the minimum number of swaps it takes to "sort"
  only the subsequence containing h < i
- dp[i] = min(dp[j] + (Number of inversions that [1, j] contributes to [j + 1, i])
                    + (Number of not inversions within the positions of [j + 1, i]))
- We can find and update the inversion stuff using two BITs
- Complexity: O(N^2 log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, pos[5001], dp[5001], bit1[5001], bit2[5001];

void update(int *bit, int pos, int val) {
    for (; pos <= n; pos += pos & -pos) bit[pos] += val;
}
int query(int *bit, int a, int b) {
    int ans = 0;
    for (; b; b -= b & -b) ans += bit[b];
    for (a--; a; a -= a & -a) ans -= bit[a];
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        pos[a] = i;
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MAX;

        // First, get inversions from [1; i]
        int inversions = 0;
        for (int j = 1; j <= i; j++) {
            inversions += query(bit1, 1, pos[j] - 1);
            update(bit1, pos[j], 1);
        }

        // Then find the best j for dp[i]
        memset(bit2, 0, sizeof bit2);
        for (int j = 0; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + inversions);
            // First, remove j + 1 from bit1 and subtract its contribution
            inversions -= query(bit1, pos[j + 1] + 1, n) + query(bit2, pos[j + 1] + 1, n);
            update(bit1, pos[j + 1], -1);
            // Next, add j + 1 to bit2
            inversions += query(bit1, 1, pos[j + 1] - 1);
            update(bit2, pos[j + 1], 1);
        }
    }
    cout << dp[n];
    return 0;
}