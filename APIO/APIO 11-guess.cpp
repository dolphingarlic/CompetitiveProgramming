/*
APIO 2011 Guess My Word
- A state in this game consists of the following info:
    - The set of candidate words (cand)
    - The set of positions whose letters are already known (mask)
    - The number of remaining wrong guesses (rem)
- If |cand| == 0 (i.e. A contradicted themselves), then B wins
- Otherwise, if rem == 0 (i.e. B made too many wrong guesses),
  then A wins
- Otherwise, if |cand| == 1 (i.e. B narrowed the set of words
  down to a single one), then B wins
- Otherwise, the following happens:
    - B must guess a letter present in one of the candidates
      in a position whose letter is still unknown
    - A then chooses whether to confirm the letter and in which
      position, or to tell B that their guess was wrong
    - If A is able to force a win by using *any* such move
      *for all* possible letters that B guesses, then A wins;
      otherwise, B wins
- No idea what the complexity is, but it's fast enough
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

string s[1000];
vector<int> has_len[8];

bool possible(int len, vector<int> cand, int mask, int rem) {
    if (!cand.size()) return false;
    if (!rem) return true;
    if (cand.size() == 1) return false;

    bool good[26];
    memset(good, 0, sizeof good);
    for (int i = 0; i < len; i++) if (!(mask & (1 << i))) {
        for (int j : cand) good[s[j][i] - 'A'] = true;
    }

    bool all = true;
    for (char i = 'A'; i <= 'Z'; i++) if (good[i - 'A']) {
        vector<vector<int>> match(len);
        vector<int> nomatch;
        for (int j : cand) {
            bool found = false;
            for (int k = 0; k < len && !found; k++) if (s[j][k] == i) {
                match[k].push_back(j);
                found = true;
            }
            if (!found) nomatch.push_back(j);
        }
        bool any = possible(len, nomatch, mask, rem - 1);
        for (int j = 0; j < len && !any; j++) if (!(mask & (1 << j)))
             any = possible(len, match[j], mask + (1 << j), rem);
        all &= any;
    }
    return all;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            has_len[s[i].size()].push_back(i);
        }
        bool any = false;
        for (int i = 1; i <= 7; i++) {
            if (!any) any = possible(i, has_len[i], 0, i + 1);
            has_len[i].clear();
        }
        cout << (any ? "Yes" : "No") << '\n';
    }
    return 0;
}
