/*
Baltic 2008 Election
- We only care about the smallest party in any coalition, so sort them in descending order
- We can then use knapsack DP + backtracking to get the maximal coaliltion
- Complexity: O(N * SUM_A)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<int, int> a[301], backtrack[100001][301];
int dp[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, tot = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
        tot += a[i].first;
    }
    sort(a + 1, a + n + 1, greater<pair<int, int>>());
    dp[0] = -1;
    pair<int, int> best;
    for (int i = 1, tot_so_far = 0; i <= n; tot_so_far += a[i++].first) {
        for (int j = min(tot_so_far, tot / 2); ~j; j--) {
            int v = j + a[i].first;
            if (!dp[j] || dp[v]) continue;
            dp[v] = i;
            backtrack[v][i] = {j, dp[j]};

            if (v > tot / 2) best = max(best, {v, i});
        }
    }
    vector<int> v;
    for (; best.first; best = backtrack[best.first][best.second]) {
        v.push_back(a[best.second].second);
    }
    cout << v.size() << '\n';
    for (int i : v) cout << i << ' ';
    return 0;
}