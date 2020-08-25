/*
Balkan 2015 Clarkson
- First, we want to find the array F where str1[i..i + F[i] - 1] is
  a substring of str2 and F[i] is maximal
    - We can solve this using a suffix array and LCP (apparently it's classical)
    - First, build the suffix array (an O(N log^2 N) implementation works) and
      the LCP array + a sparse table to get RMQ
    - Next, notice how since LCP uses range minimums, for each index i of str1
      we only need to check the LCP of two indices of str2
        - These two indices are the two closest indices to i in the suffix array
        - We can just take the maximum of these two LCPs
- Next, we binary search for the answer. Let the current candidate be len
    - Let dp[i] = Is it possible to make str1[i..N - 1] with substrings of length >= len
                = any(dp[j] for j in range(i + len, i + F[i]))
    - We can use a std::set to compute dp efficiently
- Complexity: O(N log^2 N)
*/

#include <bits/stdc++.h>
using namespace std;

string s, t, u;
int n, m, l;
int ord[200005], nord[200005], suff[200005], rev[200005], p = 1;
int lcp[200005][20], match[100000], h = 0;
set<int> topgear;

void build_suffix_arr() {
    u = s + '~' + t;
    l = n + m + 1;

    ord[l] = -1;
    for (int i = 0; i < l; i++) ord[i] = u[i], suff[i] = i;
    auto cmp = [](int A, int B) {
        if (ord[A] == ord[B]) return ord[A + p] < ord[B + p];
        return ord[A] < ord[B];
    };
    while (p <= l) {
        sort(suff, suff + l, cmp);
        nord[suff[0]] = 0;
        for (int i = 1; i < l; i++) {
            nord[suff[i]] = nord[suff[i - 1]];
            if (cmp(suff[i - 1], suff[i])) nord[suff[i]]++;
        }
        for (int i = 0; i < l; i++) ord[i] = nord[i];
        p <<= 1;
    }

    for (int i = 0; i < l; i++) rev[suff[i]] = i;
    for (int i = 0; i < l; i++) {
        if (rev[i]) {
            int j = suff[rev[i] - 1];
            while (u[i + h] == u[j + h]) h++;
            lcp[rev[i]][0] = h;
        }
        h = max(h - 1, 0);
    }

    for (int i = n + 1; i < l; i++) topgear.insert(rev[i]);
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i <= l - (1 << j); i++) {
            lcp[i][j] = min(lcp[i][j - 1], lcp[i + (1 << j - 1)][j - 1]);
        }
    }
}

int rmq(int l, int r) {
    int level = 31 - __builtin_clz(r - l  + 1);
    return min(lcp[l][level], lcp[r - (1 << level) + 1][level]);
}

bool check(int len) {
    set<int> good;
    good.insert(n);
    for (int i = n - 1; ~i; i--) {
        set<int>::iterator lb = good.lower_bound(i + len);
        if (lb != good.end() && *lb <= i + match[i]) good.insert(i);
    }
    return !*good.begin();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> s >> t;
    n = s.size(), m = t.size();

    build_suffix_arr();
    for (int i = 0; i < n; i++) {
        set<int>::iterator lb = topgear.lower_bound(rev[i]);
        if (lb != topgear.end()) match[i] = max(match[i], rmq(rev[i] + 1, *lb));
        if (lb != topgear.begin()) {
            lb--;
            match[i] = max(match[i], rmq(*lb + 1, rev[i]));
        }
    }

    int l = 0, r = n;
    while (l != r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    cout << (l ? l : -1);
    return 0;
}