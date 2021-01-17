/*
Baltic 2005 Ancient Manuscript
- dp[i][c][t][e] = Number of ways to make a word from the first i letters ending with c and
                   t consecutive vowels/consonants and e consecutive equal letters w.r.t. c
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<int> vowels = {1, 5, 9, 15, 21}, consonants;

ll dp[16][27][5][5];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 1; i <= 26; i++)
        if (vowels.find(i) == vowels.end()) consonants.insert(i);
    int ve, vc, ce, cc;
    string s;
    cin >> ve >> vc >> ce >> cc >> s;
    dp[0][0][0][0] = 1;
    for (int i = 1; i <= s.size(); i++) {
        if (s[i - 1] == '*') {
            for (int c = 1; c <= 26; c++) {
                dp[i][c][1][1] += dp[i - 1][0][0][0];
                if (vowels.find(c) != vowels.end()) {
                    for (int j : vowels) {
                        if (c == j) {
                            for (int t = 2; t <= vc; t++)
                                for (int e = 2; e <= ve; e++)
                                    dp[i][c][t][e] += dp[i - 1][j][t - 1][e - 1];
                        } else {
                            for (int t = 2; t <= vc; t++)
                                for (int e = 1; e <= ve; e++)
                                    dp[i][c][t][1] += dp[i - 1][j][t - 1][e];
                        }
                    }
                    for (int j : consonants) {
                        for (int t = 1; t <= cc; t++)
                            for (int e = 1; e <= ce; e++)
                                dp[i][c][1][1] += dp[i - 1][j][t][e];
                    }
                } else {
                    for (int j : consonants) {
                        if (c == j) {
                            for (int t = 2; t <= cc; t++)
                                for (int e = 2; e <= ce; e++)
                                    dp[i][c][t][e] += dp[i - 1][j][t - 1][e - 1];
                        } else {
                            for (int t = 2; t <= cc; t++)
                                for (int e = 1; e <= ce; e++)
                                    dp[i][c][t][1] += dp[i - 1][j][t - 1][e];
                        }
                    }
                    for (int j : vowels) {
                        for (int t = 1; t <= vc; t++)
                            for (int e = 1; e <= ve; e++)
                                dp[i][c][1][1] += dp[i - 1][j][t][e];
                    }
                }
            }
        } else {
            int c = s[i - 1] - 'a' + 1;
            dp[i][c][1][1] += dp[i - 1][0][0][0];
            if (vowels.find(c) != vowels.end()) {
                for (int j : vowels) {
                    if (c == j) {
                        for (int t = 2; t <= vc; t++)
                            for (int e = 2; e <= ve; e++)
                                dp[i][c][t][e] += dp[i - 1][j][t - 1][e - 1];
                    } else {
                        for (int t = 2; t <= vc; t++)
                            for (int e = 1; e <= ve; e++)
                                dp[i][c][t][1] += dp[i - 1][j][t - 1][e];
                    }
                }
                for (int j : consonants) {
                    for (int t = 1; t <= cc; t++)
                        for (int e = 1; e <= ce; e++)
                            dp[i][c][1][1] += dp[i - 1][j][t][e];
                }
            } else {
                for (int j : consonants) {
                    if (c == j) {
                        for (int t = 2; t <= cc; t++)
                            for (int e = 2; e <= ce; e++)
                                dp[i][c][t][e] += dp[i - 1][j][t - 1][e - 1];
                    } else {
                        for (int t = 2; t <= cc; t++)
                            for (int e = 1; e <= ce; e++)
                                dp[i][c][t][1] += dp[i - 1][j][t - 1][e];
                    }
                }
                for (int j : vowels) {
                    for (int t = 1; t <= vc; t++)
                        for (int e = 1; e <= ve; e++)
                            dp[i][c][1][1] += dp[i - 1][j][t][e];
                }
            }
        }
    }
    ll ans = 0;
    for (int c = 1; c <= 26; c++) for (int t = 1; t <= 4; t++) for (int e = 1; e <= 4; e++)
        ans += dp[s.size()][c][t][e];
    cout << ans;
}
