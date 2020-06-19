/*
COI 2008 Izbori
- For subtask 1, we can just give all remaining votes to the party whose
  seats we want to maximize
    - Then just simulate the process in O(MN^2) time
- For subtask 2, first notice how if we can force party i to have at most X
  seats, we can also force it to have at most X + 1 seats
- Let dp[i][j][k][l] = Minimum number of votes we need to distribute to other
                       parties such party i wins l seats and the other parties
                       win j seats when only considering the first k such parties
- Notice how we only need to calculate dp for at most 20 parties because
  of the 5% threshold (all parties initially with < 5% of V get 0 seats)
- Additionally, since dp[i][j][k] increases as l decreases, we can binary search
  for the smallest l such that dp[i][N - 1][M - l][l] <= remaining votes
- This gets rid of 2 dimensions already (we now only do dp[j][k])
- Now imagine for some i and l, we want party x to win incr seats
    - The final quotient of party i is curr[i] / (l + 1)
    - We want the quotient of party x to be at least this when it takes incr - 1
      seats, so we get
      (curr[x] + added votes) / incr >= curr[i] / (l + 1)
    - So set (curr[x] + added votes) = ceil(curr[i] * incr / (l + 1))
    - If x > i, we may also need to increment this by 1 to make sure x is chosen
      instead of i
    - Finally, we also need to make sure (curr[x] + added votes) >= 5% of V (so 
      that party x actually gets those seats)
    - This gives us a way to calculate dp in O(NM^2)
- Complexity: O(20 NM^2 log M)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Frac {
    int idx, num, denom;
    Frac(int I = 101, int N = 0, int D = 1) : idx(I), num(N), denom(D) {}
};
bool operator<(Frac A, Frac B) {
    if (A.num * B.denom == B.num * A.denom) return A.idx > B.idx;
    return A.num * B.denom < B.num * A.denom;
}

int curr[101], s[101], mx[101], other[101], dp[101][201];

int required(int j, int i, int incr, int mid) {
    int x = (curr[i] * incr + mid) / (mid + 1);
    if (x * (mid + 1) == curr[i] * incr && j > i) x++;
    x = max(x, curr[j]);
    return x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int v, rem, n, m;
    cin >> v >> n >> m;
    rem = v;
    FOR(i, 1, n + 1) {
        cin >> curr[i];
        rem -= curr[i];
    }

    // Subtask 1
    FOR(i, 1, n + 1) {
        curr[i] += rem;
        FOR(i, 1, n + 1) s[i] = 0;
        FOR(j, 1, m + 1) {
            Frac best;
            FOR(k, 1, n + 1) {
                if (curr[k] * 100 < v * 5) continue;
                best = max(best, {k, curr[k], s[k] + 1});
            }
            s[best.idx]++;
        }
        cout << (mx[i] = s[i]) << " \n"[i == n];
        curr[i] -= rem;
    }
    cout << '\n';

    // Subtask 2
    FOR(i, 1, n + 1) {
        if (curr[i] * 100 < v * 5) {
            cout << 0 << " \n"[i == n];
            continue;
        }

        int l = 0, r = mx[i], opt;
        while (l <= r) {
            int mid = (l + r) / 2, o = 0;
            FOR(j, 1, n + 1) if (j != i) other[++o] = j;
            memset(dp, 0x3f, sizeof(dp));
            dp[0][0] = 0;

            FOR(j, 0, o) FOR(tot, 0, m - mid + 1) {
                dp[j + 1][tot] = min(dp[j + 1][tot], dp[j][tot]);
                FOR(incr, 1, m - mid - tot + 1) {
                    int x = required(other[j + 1], i, incr, mid);
                    if (x * 100 < v * 5) x = (v * 5 + 99) / 100;
                    dp[j + 1][tot + incr] =
                        min(dp[j + 1][tot + incr],
                            dp[j][tot] + x - curr[other[j + 1]]);
                }
            }

            if (dp[o][m - mid] <= rem) {
                opt = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << opt << " \n"[i == n];
    }
    return 0;
}