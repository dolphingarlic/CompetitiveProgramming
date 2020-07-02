/*
Baltic 2019 Necklace
- Firstly, assume WLOG that we can't flip the necklace.
    - If we do flip it in the optimal solution, just reverse B and run the
      same solution again
- Notice how we'll have A = ...XY... and B = ...YX... where X and Y are substrings
- lcs[i][j] = Longest common suffix of A[:i] and B[:j]
            = lcs[i - 1][j - 1] + 1 if A[i] == B[j] else 0
- dp1[i][j] = Longest suffix of A[:i] that's also a prefix of B[j:]
    - First, dp1[i][j - lcs[i][j]] = max(dp1[i][j - lcs[i][j]], lcs[i][j])
    - Next, dp1[i][j] = max(dp1[i][j], dp1[i][j - 1] - 1)
- dp2[i][j] = Longest prefix of A[i:] that's also a suffix of B[:j]
    - We compute this similarly
- To get this down to O(N) memory, notice how dp[i] only depends on lcs[i]
  and lcs[i] only depends on lcs[i - 1]
- Complexity: O(N^2) with O(N) memory
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int lcs[3001][3001], dp1[3001][3001], dp2[3001][3001];
int mx_len, best_i, best_j;

void solve(string A, string B, bool reversed) {
    memset(lcs, 0, sizeof lcs);
    memset(dp1, 0, sizeof dp1);
    memset(dp2, 0, sizeof dp2);
    FOR(i, 1, A.size() - 1) {
        FOR(j, 1, B.size() - 1) {
            lcs[i][j] = (A[i] == B[j] ? lcs[i - 1][j - 1] + 1 : 0);
            dp1[i][j - lcs[i][j]] = max(dp1[i][j - lcs[i][j]], lcs[i][j]);
            dp2[i - lcs[i][j]][j] = max(dp2[i - lcs[i][j]][j], lcs[i][j]);
        }
    }
    FOR(i, 1, A.size() - 1) {
        FOR(j, 1, B.size() - 1) {
            dp1[i][j] = max(dp1[i][j], dp1[i][j - 1] - 1);
            dp2[i][j] = max(dp2[i][j], dp2[i - 1][j] - 1);

            if (dp1[i][j] + dp2[i][j] > mx_len) {
                mx_len = dp1[i][j] + dp2[i][j];
                best_i = i - dp1[i][j];
                if (!reversed) best_j = j - dp2[i][j];
                else best_j = B.size() - j - dp1[i][j] - 2;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string A, B;
    cin >> A >> B;
    A = "." + A + ".", B = "." + B + ".";
    solve(A, B, 0);
    reverse(B.begin(), B.end());
    solve(A, B, 1);
    cout << mx_len << '\n' << best_i << ' ' << best_j;
    return 0;
}