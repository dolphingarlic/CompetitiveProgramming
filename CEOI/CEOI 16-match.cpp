/*
CEOI 2016 Match
- Let match(i, j) = Can we make a balanced bracket sequence from s[i:j]?
- First, check if match(0, N - 1) and print -1 if not
- Next, notice how we want to match opening brackets as late as possible
    - This means that given s[i:j] where match(i, j), s[i] matches with
      the greatest k such that match(k + 1, j) and s[k] == s[i]
- Let opt[j][c] = The greatest k such that match(k + 1, j) and s[k] == c
                = j                                 if s[j] == c,
                  opt[opt[j - 1][s[j]] - 1][c]      if j > 0 and opt[j - 1][s[j]] > 0
                  -1                                otherwise
- Clearly, this can be precomputed in O(26N) time and memory
- Now we can recursively solve for the optimal string, since we know we match
  s[i] with s[opt[j][s[i]]] for the substring s[i:j]
- Complexity: O(26N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

string s;
int n, opt[100000][26];
char ans[100000];

string solve(int l = 0, int r = n - 1) {
    if (l > r) return "";
    return '(' + solve(l + 1, opt[r][s[l] - 'a'] - 1) + ')' + solve(opt[r][s[l] - 'a'] + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    n = s.size();
    stack<char> stck;
    FOR(i, 0, n) {
        if (stck.size() && s[i] == stck.top()) stck.pop();
        else stck.push(s[i]);
        FOR(j, 0, 26) {
            if (j == s[i] - 'a') opt[i][j] = i;
            else if (i && opt[i - 1][s[i] - 'a']) opt[i][j] = opt[opt[i - 1][s[i] - 'a'] - 1][j];
            else opt[i][j] = -1;
        }
    }
    if (stck.size()) return cout << -1, 0;
    cout << solve();
    return 0;
}