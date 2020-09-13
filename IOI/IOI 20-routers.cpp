/*
IOI 2020 Routers
- We basically want to find the midpoints of each segment
- First, binary search for the ranges containing exactly 1 midpoint
- Then we binary search on each of these ranges for the actual midpoints
- Complexity: At most 7500 queries
*/

#include "routers.h"

#include <bits/stdc++.h>
using namespace std;

pair<int, int> rng[1000];

void search_ranges(int l, int r, int a, int b) {
    if (a > b) return;
    if (a == b) {
        rng[a] = {l, r};
        return;
    }
    int mid = (l + r + 1) / 2;
    int piv = use_detector(mid);
    search_ranges(l, mid - 1, a, piv);
    search_ranges(mid, r, piv + 1, b);
}

vector<int> find_routers(int len, int n, int q) {
    search_ranges(0, len, 1, n - 1);
    vector<int> ans = {0};
    for (int i = 1; i < n; i++) {
        int l, r;
        tie(l, r) = rng[i];
        while (l != r) {
            int mid = (l + r + 1) / 2;
            if (use_detector(mid) == i) r = mid - 1;
            else l = mid;
        }
        ans.push_back(2 * l - ans.back());
    }
    return ans;
}
