/*
Baltic 2008 Gloves
- First, get rid of all colours with only gloves of one handedness and add
  their counts to the "baseline" answers
- If we take x right gloves, how many left ones do we need to take to get a match?
    - The answer is
        max(sum(B[i] : i not in S) + 1 : |S| <= x <= sum(A[i] : i in S))
    - Since all A[i] > 0 though, this simplifies to
        max(sum(B[i] : i not in S) + 1 : x <= sum(A[i] : i in S))
- If we draw the "forbidden" pairs of gloves we can take on the Cartesian plane,
  they form a staircase shape
- We can therefore find sum(A[i] : i in S) and sum(B[i] : i not in S) for each
  subset S of {1, 2, ..., N}, and use a monostack to find this staircase shape
- The answer must lie at a vertex of this shape, and there are O(2^N) vertices
- Complexity: O(N * 2^N)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, l[20], r[20];
    cin >> n;
    for (int i = 0; i < n; i++) cin >> l[i];
    for (int i = 0; i < n; i++) cin >> r[i];

    int m = 0, base_l = 0, base_r = 0;
    for (int i = 0; i < n; i++) {
        if (l[i] && r[i]) {
            l[m] = l[i], r[m] = r[i];
            m++;
        } else base_l += l[i], base_r += r[i];
    }

    vector<pair<int, int>> points;
    for (int mask = 1; mask < (1 << m); mask++) {
        int l_sum = 0, r_sum = 0;
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) l_sum += l[i];
            else r_sum += r[i];
        }
        points.push_back({l_sum, r_sum});
    }
    sort(points.begin(), points.end());

    vector<pair<int, int>> stck = {{0, INT_MAX}};
    for (pair<int, int> i : points) {
        while (stck.back().second < i.second) stck.pop_back();
        stck.push_back(i);
    }
    stck.push_back({INT_MAX, 0});

    pair<int, int> ans = {INT_MAX, 0};
    for (int i = 1; i < stck.size(); i++) {
        pair<int, int> cand = {stck[i - 1].first + 1, stck[i].second + 1};
        if (cand.first + cand.second < ans.first + ans.second) ans = cand;
    }
    cout << ans.first + base_l << '\n' << ans.second + base_r;
    return 0;
}
