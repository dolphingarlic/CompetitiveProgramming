/*
Balkan 2017 Cats
- Observation 1: We will never move an animal twice
- Observation 2: The order of moves doesn't matter
    - This means we can effectively take out a subset of animals
      and insert them at various locations
- First, handle the corner cases
    - There are only 1s or 0s
    - There are no 2s
- Next, consider dp[i][num2][last][i0][i1]
    - i = Prefix/suffix position we're considering
    - num2 = Number of 2s we've placed so far
    - last = What animal we have last currently
    - i0, i1 = Do we have a 0 or 1 in the prefix/suffix
- We either leave the animal or move it to the prefix
    - For 0 and 1, if we don't move it then we may need a 2 to
      resolve conflicts
    - For 2, we can freely leave it or move it
- Notice that dp[i] only depends on dp[i - 1] so we can optimize
  memory to O(N)
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define v vector
typedef long long ll;
using namespace std;

void mineq(int& A, int B) { A = min(A, B); }

int solve() {
    int n;
    cin >> n;
    v<int> cnt(3), a(n);
    FOR(i, 0, n) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    if (!cnt[0] || !cnt[1]) return 0;
    if (!cnt[2]) return -1;
    cnt[2]++;

    v<v<v<v<v<int>>>>> dp(2, v<v<v<v<int>>>>(2 * cnt[2] + 1, v<v<v<int>>>(3, v<v<int>>(2, v<int>(2, 1e5)))));

    for (int i = n; i >= 0; i--) {
        FOR(num2, 1, 2 * cnt[2]) {
            FOR(last, 0, 3) {
                FOR(i0, 0, 2) {
                    FOR(i1, 0, 2) {
                        if (i == n) {
                            if (num2 == cnt[2] && ((i0 + i1 + (last == 2)) > 1))
                                dp[i & 1][num2][last][i0][i1] = 0;
                            else
                                dp[i & 1][num2][last][i0][i1] = 1e5;
                            continue;
                        }

                        dp[i & 1][num2][last][i0][i1] = dp[1 - i & 1][num2][last][i0][i1] + 1;

                        switch (a[i]) {
                            case 0:
                                if (last != 1)
                                    mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2][0][1][i1]);
                                mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2 + 1][0][1][i1]);
                                break;
                            case 1:
                                if (last != 0)
                                    mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2][1][i0][1]);
                                mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2 + 1][1][i0][1]);
                                break;
                            default:
                                if (last == 2) {
                                    mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2][2][i0][1]);
                                    mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2][2][1][i1]);
                                }
                                mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2][2][i0][i1]);
                                mineq(dp[i & 1][num2][last][i0][i1], dp[1 - i & 1][num2 - 1][last][i0][i1] + 1);
                        }
                    }
                }
            }
        }
    }
    return dp[0][cnt[2]][2][0][0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) cout << solve() << '\n';
    return 0;
}