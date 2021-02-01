/*
Baltic 2019 Necklace
- Assume for simplicity that we can't flip over the necklace
- For each i from 0 to N...
    - Let S1 = reversed(S[0 .. i - 1]) and S2 = S[i .. N - 1]
    - Let T1 = T and T2 = reversed(T)
    - Construct the prefix functions of the strings (S1 + "#" + T1) and (S2 + "#" + T2)
    - Using these prefix functions, we can find the longest necklaces we can make if we
      rotate it so that bead S[i] is at the front
- Afterward, reverse T and solve the problem again
- Complexity: O(N^2) with O(N) memory
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int p1[6002], p2[6002];

void fill_p(string s, int *p) {
    for (int i = 1; i < s.size(); i++) {
        int j = p[i - 1];
        while (j && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
}

tuple<int, int, int> solve(string s, string t, bool rev) {
    int n = s.size(), m = t.size();
    tuple<int, int, int> ans = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        string s1 = s.substr(0, i), s2 = s.substr(i, n - i);
        reverse(s1.begin(), s1.end());
        string t1 = t, t2 = t;
        reverse(t2.begin(), t2.end());
        fill_p(s1 + "#" + t1, p1), fill_p(s2 + "#" + t2, p2);
        for (int j = 1; j <= m; j++)
            ans = max(ans, {
                p1[i + j] + p2[n + m - i - j],
                i - p1[i + j],
                rev ? m - j - p2[n + m - i - j] : j - p1[i + j]
            });
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    tuple<int, int, int> ans = solve(s, t, false);
    reverse(t.begin(), t.end());
    ans = max(ans, solve(s, t, true));
    cout << get<0>(ans) << '\n' << get<1>(ans) << ' ' << get<2>(ans);
    return 0;
}
