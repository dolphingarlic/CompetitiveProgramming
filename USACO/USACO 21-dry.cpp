/*
USACO 2021 No Time to Dry
- Wow another banger problem by Andi Qu - I wonder who he is?
- Use D&C to answer the queries
- Assume that all our queries lie in the range [l, r]
    - Let mid = (l + r) / 2
    - Split the queries into three lists:
        1) b <= mid
        2) a > mid
        3) a <= mid < b
- We can solve the first two lists on the ranges [l, mid] and [mid + 1, r]
- Next, we solve the third list:
- We first use two monotone stacks to compute the answer for prefixes/suffixes
  of C[l : mid] and C[mid + 1 : r]
- Next, we use two more monotone stacks to find the list of "critical" colours
    - i.e. Colours we can use to bridge the gap between [l, mid] and [mid + 1, r]
- The answer for a query is simply
    suff[a : mid] + pref[mid + 1 : b] - (Number of common critical colours in the two ranges)
- We can find the second part using binary search
- Since we recurse O(log N) times and each "layer" takes O(N log N) time to solve,
  this is amortized O(N log^2 N) time
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int c[200000], ans[200000];
vector<pair<int, int>> todo[200000];
int prefsuff[200000], good[200000];

void solve(int l, int r, vector<tuple<int, int, int>> &queries) {
    if (!queries.size()) return;

    if (l != r) {
        int mid = (l + r) / 2;
        vector<tuple<int, int, int>> ql, qr, qm;
        for (auto i : queries) {
            if (get<2>(i) <= mid) ql.push_back(i);
            else if (get<1>(i) > mid) qr.push_back(i);
            else qm.push_back(i);
        }
        solve(l, mid, ql);
        solve(mid + 1, r, qr);
        
        for (auto i : qm) todo[get<1>(i)].push_back({get<0>(i), get<2>(i)});

        // Use monostack to find prefix/suffix stuff
        vector<int> stck;
        for (int i = mid + 1; i <= r; i++) {
            if (i == mid + 1) prefsuff[i] = 0;
            else prefsuff[i] = prefsuff[i - 1];
            // Keep the colours in the stack strictly increasing
            while (stck.size() && c[i] < c[stck.back()]) stck.pop_back();
            if (!stck.size()) { // Found a new prefix minimum
                good[c[i]] = i;
            }
            // Update the monostwack
            if (!stck.size() || c[i] != c[stck.back()]) stck.push_back(i), prefsuff[i]++;
        }
        stck.clear();
        vector<int> found;
        for (int i = mid; i >= l; i--) {
            if (i == mid) prefsuff[i] = 0;
            else prefsuff[i] = prefsuff[i + 1];
            // Keep the colours in the stack strictly increasing
            while (stck.size() && c[i] < c[stck.back()]) stck.pop_back();
            if (!stck.size()) { // Found a new prefix minimum
                if (good[c[i]]) found.push_back(good[c[i]]);
            }
            // Update the monostack
            if (!stck.size() || c[i] != c[stck.back()]) stck.push_back(i), prefsuff[i]++;
            // Process the queries with left endpoint here
            for (pair<int, int> j : todo[i]) {
                int ub = upper_bound(found.begin(), found.end(), j.second) - found.begin();
                ans[j.first] = prefsuff[i] + prefsuff[j.second] - ub;
            }
            todo[i].clear();
        }

        // Reset stuff
        for (int i = mid + 1; i <= r; i++) good[c[i]] = 0;
    } else for (auto i : queries) ans[get<0>(i)] = 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> c[i];
    vector<tuple<int, int, int>> queries(n);   
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = {i, l, r};
    }
    solve(0, n - 1, queries);
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}
