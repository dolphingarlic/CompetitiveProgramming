/*
IOI 2011 Elephants
- The greedy strategy for placing cameras works
- Split the elephants into sqrt N buckets
- Let dp[i] = The number of cameras and extent of cameras such that they cover elephant i's bucket
              if the first camera is on elephant i and a minimum number of cameras is used
- We can compute all dp[i] in a bucket in O(sqrt N log N) time
- Moving an elephant affects at most 2 buckets
- Additionally, we "reset" buckets every sqrt N queries to keep the bucket sizes balanced
- Complexity: O(N sqrt N log N)
*/

#include "elephants.h"

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define ALL(x) x.begin(), x.end()
using namespace std;

const int MX_N = 150000, B = 300, IB = 500;

int n, l, x[MX_N];
vector<pair<int, int>> bckt[IB];
int b_idx[MX_N];
pair<int, int> dp[MX_N];
int to_reset;
pair<int, int> by_x[MX_N];

inline void reset() {
    for (int i = 0; i < n; i++) by_x[i] = {x[i], i};
    sort(by_x, by_x + n);
    for (int i = 0; i < IB; i++) bckt[i].clear();
    for (int i = 0; i < n; i++) {
        bckt[i / B].push_back(by_x[i]);
        b_idx[by_x[i].second] = i / B;
    }
    for (int i = 0; i < IB; i++) {
        for (int j = bckt[i].size() - 1; ~j; j--) {
            int ub = upper_bound(ALL(bckt[i]), make_pair(bckt[i][j].first + l, INT_MAX)) - bckt[i].begin();
            if (ub == int(bckt[i].size())) dp[bckt[i][j].second] = {1, bckt[i][j].first + l};
            else {
                dp[bckt[i][j].second] = dp[bckt[i][ub].second];
                dp[bckt[i][j].second].first++;
            }
        }
    }
    to_reset = 3 * B;
}

void init(int N, int L, int X[]) {
    n = N, l = L;
    for (int i = 0; i < n; i++) x[i] = X[i];
    reset();
}

int update(int i, int y) {
    // Erase elephant i and update bucket
    bckt[b_idx[i]].erase(find(ALL(bckt[b_idx[i]]), make_pair(x[i], i)));
    for (int j = bckt[b_idx[i]].size() - 1; ~j; j--) {
        int ub = upper_bound(ALL(bckt[b_idx[i]]), make_pair(bckt[b_idx[i]][j].first + l, INT_MAX)) - bckt[b_idx[i]].begin();
        if (ub == int(bckt[b_idx[i]].size())) dp[bckt[b_idx[i]][j].second] = {1, bckt[b_idx[i]][j].first + l};
        else {
            dp[bckt[b_idx[i]][j].second] = dp[bckt[b_idx[i]][ub].second];
            dp[bckt[b_idx[i]][j].second].first++;
        }
    }
    // Insert elephant i and update bucket
    x[i] = y;
    for (int new_b = 0; new_b < IB; new_b++) {
        if ((bckt[new_b].size() && bckt[new_b].back().first >= x[i]) || new_b == IB - 1) {
            bckt[new_b].insert(upper_bound(ALL(bckt[new_b]), make_pair(x[i], i)), make_pair(x[i], i));
            for (int j = bckt[new_b].size() - 1; ~j; j--) {
                int ub = upper_bound(ALL(bckt[new_b]), make_pair(bckt[new_b][j].first + l, INT_MAX)) - bckt[new_b].begin();
                if (ub == int(bckt[new_b].size())) dp[bckt[new_b][j].second] = {1, bckt[new_b][j].first + l};
                else {
                    dp[bckt[new_b][j].second] = dp[bckt[new_b][ub].second];
                    dp[bckt[new_b][j].second].first++;
                }
            }
            b_idx[i] = new_b;
            break;
        }
    }
    // Reset buckets after B queries
    if (!--to_reset) reset();
    // Get the answer
    int ans = 0;
    for (int j = 0, curr_x = -1; j < IB; j++) if (bckt[j].size() && curr_x < bckt[j].back().first) {
        int ub = upper_bound(ALL(bckt[j]), make_pair(curr_x, INT_MAX))->second;
        ans += dp[ub].first;
        curr_x = dp[ub].second;
    }
    return ans;
}
