/*
POI 2005 Template
- Same as amortized O(N), but we only check O(log N) candidates and we check the whole string
*/

#include <bits/stdc++.h>
using namespace std;

string s;
int p[500000];

int shortest_template(int n) {
    if (!p[n - 1]) return n;
    if (p[n - 1] * 2 >= n) return shortest_template(p[n - 1]);
    int cand = shortest_template(p[n - 1]);
    for (int i = 0, j = 0, curr = -1; i < n; i++) {
        while (j && (j == cand || s[i] != s[j])) j = p[j - 1];
        if (s[i] == s[j]) j++;
        if (j == cand) curr = i;
        if (i - curr >= cand) return n;
    }
    return cand;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> s;
    int n = s.size();
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1];
        while (p[i] && s[i] != s[p[i]]) p[i] = p[p[i] - 1];
        if (s[i] == s[p[i]]) p[i]++;
    }
    cout << shortest_template(n);
    return 0;
}
