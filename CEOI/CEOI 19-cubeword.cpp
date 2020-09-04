/*
CEOI 2019 Cubeword
- Assume WLOG that all words are of the same length
- Let dp[a][b][c] = The number of triples of words that start with the same letter
                    and end with a, b, and c respectively
    - dp[a][b][c] = dp[a][c][b] = dp[b][a][c] = ...
      so we can compute dp in O(S^4 / 24)
- Imagine we know the letters on the vertices of the "inner tetrahedron" of the cube
    - Assuming these letters are a, b, c, and d, the number of ways to fill in the
      rest of the letters is dp[a][b][c] * dp[a][b][d] * dp[a][c][d] * dp[b][c][d]
- Notice how we can rotate the cube and get different cubewords, so we can assume
  that a <= b <= c <= d and multiply the result by the number of distinct permutations
  of (a, b, c, d)
    - This cuts the computation down from O(S^4) to O(S^4 / 24)
- Complexity: O(N + S^4 / 24)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 998244353;

inline int id(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 52;
}

set<string> words[11];
ll cnt[62][62], dp[62][62][62], perm[8] = {24, 12, 12, 4, 12, 6, 4, 1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        words[s.size()].insert(s);
        reverse(s.begin(), s.end());
        words[s.size()].insert(s);
    }

    ll ans = 0;
    for (int l = 3; l < 11; l++) {
        memset(cnt, 0, sizeof cnt);
        memset(dp, 0, sizeof dp);
        for (string i : words[l]) cnt[id(i[0])][id(i.back())]++;
        for (int i = 0; i < 62; i++) {
            for (int a = 0; a < 62; a++) {
                for (int b = a; b < 62; b++) {
                    for (int c = b; c < 62; c++) {
                        dp[a][b][c] = (dp[a][b][c] + cnt[i][a] * cnt[i][b] % MOD * cnt[i][c] % MOD) % MOD;
                    }
                }
            }
        }
        for (int a = 0; a < 62; a++) {
            for (int b = a; b < 62; b++) {
                for (int c = b; c < 62; c++) {
                    for (int d = c; d < 62; d++) {
                        int mask = (a == b) << 2 | (b == c) << 1 | (c == d);
                        ans = (ans + dp[a][b][c] * dp[a][b][d] % MOD * dp[a][c][d] % MOD * dp[b][c][d] % MOD * perm[mask] % MOD) % MOD;
                    }
                }
            }
        }
    }
    cout << ans;
    return 0;
}