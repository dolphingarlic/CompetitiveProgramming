/*
Balkan OI 2015 Circus
- Firstly, note that the optimal path can involve a direction change
    - An example of this is P = {1, 5, 9}, M = 13 and D = 6. Notice how
      6 -> 1 -> 5 -> 9 -> 13 is better than 6 -> 13
- An easy O(N^2 log N) solution is just to run Dijkstra from M to get
  the minimum lengths from the ceiling we need to reach M from each rope
    - We can then use a monotone stack to answer queries in O(log N) time
- The crucial observation for this problem is that the optimal path
  changes direction at most twice
    - i.e. The optimal path: right (possibly 0) -> left (possibly 0) -> right
    - No idea how to prove this though
- Drawing from the monotone stack method to answer queries, we can do this:
    - First, use monotone stack to find the minimum lengths needed if we
      only move right
    - Next, use monotone stack to find the minimum lengths needed if we
      only move left (possibly 0) -> right
    - Finally, use monotone stack to find the minimum lengths needed if we
      move right (possibly 0) -> left (possibly 0) -> right
- Complexity: O((N + Q) log N) 
*/

#include "circus.h"

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> p, mn;
deque<pair<int, int>> to_left, to_right;

void init(int N, int M, int P[]) {
    for (int i = 0; i < N; i++) p.push_back(P[i]);
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    n = p.size(), m = M;

    mn = vector<int>(n, INT_MAX);
    for (int i = n - 1; ~i; i--) {
        int dist = m - p[i];
        auto lb = lower_bound(to_left.begin(), to_left.end(), make_pair(p[i], 0));
        if (lb != to_left.end()) dist = min(dist, lb->second - p[i]);
        mn[i] = min(mn[i], dist);
        while (to_left.size() && p[i] - mn[i] >= to_left[0].first)
            to_left.pop_front();
        to_left.push_front({p[i] - mn[i], p[i]});
    }
    to_left.clear();

    for (int i = 0; i < n; i++) {
        int dist = m - p[i];
        auto ub = upper_bound(to_right.begin(), to_right.end(), make_pair(p[i], INT_MAX));
        if (ub != to_right.begin()) dist = min(dist, p[i] - prev(ub)->second);
        mn[i] = min(mn[i], dist);
        while (to_right.size() && p[i] + mn[i] <= to_right.back().first)
            to_right.pop_back();
        to_right.push_back({p[i] + mn[i], p[i]});
    }
    to_right.clear();

    for (int i = n - 1; ~i; i--) {
        int dist = m - p[i];
        auto lb = lower_bound(to_left.begin(), to_left.end(), make_pair(p[i], 0));
        if (lb != to_left.end()) dist = min(dist, lb->second - p[i]);
        mn[i] = min(mn[i], dist);
        while (to_left.size() && p[i] - mn[i] >= to_left[0].first)
            to_left.pop_front();
        to_left.push_front({p[i] - mn[i], p[i]});
    }
    to_left.clear();

    for (int i = 0; i < n; i++)
        if (!to_left.size() || p[i] - mn[i] > to_left.back().first)
            to_left.push_back({p[i] - mn[i], p[i]});
    for (int i = n - 1; ~i; i--)
        if (!to_right.size() || p[i] + mn[i] < to_right[0].first)
            to_right.push_front({p[i] + mn[i], p[i]});
}

int minLength(int D) {
    int ans = m - D;
    auto lb = lower_bound(to_left.begin(), to_left.end(), make_pair(D, 0));
    if (lb != to_left.end()) ans = min(ans, lb->second - D);
    auto ub = upper_bound(to_right.begin(), to_right.end(), make_pair(D, INT_MAX));
    if (ub != to_right.begin()) ans = min(ans, D - prev(ub)->second);
    return ans;
}