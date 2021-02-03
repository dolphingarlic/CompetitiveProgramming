/*
POI 2005 Template
- Lemma 1: If T is a template of S, then any template of T is also a template of S
- Lemma 2: The shortest template of S is either itself or the shortest template of the longest prefix-suffix of S
- We can find the longest prefix-suffix of each prefix of S using KMP
- Let the prefix function be P
- We can then do the following:
    - Given S:
    - Find shortest_template(S[0 .. P[|S| - 1]])
    - Check whether this candidate is also a template of S
    - If it is, return it
    - Otherwise, return S
- But how do we check whether some string is a template of S efficiently?
- First, do KMP again, but using only the "relevant" suffix
    - i.e. S[P[|S| - 1] + 1 .. N - 1]
    - We want to find the number of matches with the candidate
- Next, we can just check whether the max gap between candidates is at most |cand|
- This seems like O(N^2), but we test each character in the suffix exactly once, so it's amortized O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

string s;
int p1[500000], p2[500000];

int shortest_template(int n) {
    if (!p1[n - 1]) return n;
    int cand = shortest_template(p1[n - 1]);
    p2[p1[n - 1] - 1] = cand;
    for (int i = p1[n - 1], curr = p1[n - 1] - 1; i < n; i++) {
        p2[i] = p2[i - 1];
        while (p2[i] && (p2[i] == cand || s[i] != s[p2[i]])) p2[i] = p1[p2[i] - 1];
        if (s[i] == s[p2[i]]) p2[i]++;

        if (p2[i] == cand) curr = i;
        if (i - curr >= cand) return n;
    }
    return cand;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> s;
    int n = s.size();
    for (int i = 1; i < n; i++) {
        p1[i] = p1[i - 1];
        while (p1[i] && s[i] != s[p1[i]]) p1[i] = p1[p1[i] - 1];
        if (s[i] == s[p1[i]]) p1[i]++;
    }
    cout << shortest_template(n);
    return 0;
}
