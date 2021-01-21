/*
IOI 2017 Ancient Books
- The base cost will be sum(|P[i] - i|) for each i
- Case S = 0:
    - Consider the cycles formed from the permutation
    - If two cycles "overlap", then Aryan can sort them simultaneously at no extra cost
    - We can thus "merge" overlapping cycles and discard any books that Aryan won't walk past
    - The extra cost will be 2 * (No. of unmerged cycles - 1)
- We can extend this idea to work with S != 0
- Let extend(l, r) = Given l and r, find the bounds of the merged cycle containing [l, r]
    - We can compute extend(l, r) in amortized linear time
- Let dp[l, r] = Minimum extra cost Aryan needs given that all books in [l, r] are sorted
               = 0 if [l, r] == The entire range of books Aryan needs to sort
                 2 + min(dp[extend(l - 1, r)], dp[extend(l, r + 1)]) otherwise
- We can reduce the number of states we visit by noticing that if extend(l - 1, r)^x contains
  extend(l, r + 1) and extend(l, r + 1)^y contains extend(l - 1, r), then we know that
  extend(l - 1, r)^x == extend(l, r + 1)^y
- This means that the extra cost is simply 2 * min(x, y), and we can find each min(x, y) for
  each [l, r] in amortized linear time
- Complexity: O(N)
*/

#include "books.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int crit_l, crit_r;
int cmp[1000000], cmp_l[1000000], cmp_r[1000000];

void extend(int &l, int &r) {
    int ext_l = min(cmp_l[cmp[l]], cmp_l[cmp[r]]);
    int ext_r = max(cmp_r[cmp[l]], cmp_r[cmp[r]]);
    while (l != ext_l || r != ext_r) {
        if (l != ext_l) {
            l--;
            ext_l = min(ext_l, cmp_l[cmp[l]]);
            ext_r = max(ext_r, cmp_r[cmp[l]]);
        } else {
            r++;
            ext_l = min(ext_l, cmp_l[cmp[r]]);
            ext_r = max(ext_r, cmp_r[cmp[r]]);
        }
    }
}

ll compute(int l, int r) {
    extend(l, r);
    if (l == crit_l && r == crit_r) return 0;
    if (l == crit_l) return compute(l, r + 1) + 2;
    if (r == crit_r) return compute(l - 1, r) + 2;

    ll to_l = 2;
    int nl = l - 1, nr = r, tl = l, tr = r + 1;
    extend(nl, nr), extend(tl, tr);
    while (nl != crit_l && nr < tr) {
        to_l += 2;
        nl--;
        extend(nl, nr);
    }
    if (nr < tr) return to_l + compute(nl, nr);

    ll to_r = 2;
    nl = l, nr = r + 1, tl = l - 1, tr = r;
    extend(nl, nr), extend(tl, tr);
    while (nl > tl) {
        to_r += 2;
        nr++;
        extend(nl, nr);
    }
    return min(to_l, to_r) + compute(nl, nr);
}

ll minimum_walk(vector<int> p, int s) {
    int n = p.size(), cmp_cnt = 0;
    fill(cmp, cmp + n, -1);
    crit_l = s, crit_r = s;
    ll intra = 0;
    for (int i = 0; i < n; i++) {
        intra += abs(p[i] - i);
        if (cmp[i] == -1) {
            int curr = i;
            cmp_l[cmp_cnt] = cmp_r[cmp_cnt] = i;
            do {
                cmp[curr] = cmp_cnt;
                cmp_r[cmp_cnt] = max(cmp_r[cmp_cnt], curr);
                curr = p[curr];
            } while (curr != i);
            if (i != p[i]) {
                crit_l = min(crit_l, cmp_l[cmp_cnt]);
                crit_r = max(crit_r, cmp_r[cmp_cnt]);
            }
            cmp_cnt++;
        }
    }
    return intra + compute(s, s);
}
