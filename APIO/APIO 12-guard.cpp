/*
APIO 2012 Guard
- First, yeet all the bushes that we know for certain contain no ninja (type-0 guards)
- Next, check each type-1 guard and see whether it's watching exactly 1 un-yeeted bush
    - If so, that bush must contain a ninja, so we yeet it, along with any type-1 guard
      that watches that bush
    - Also reduce K by the number of bushes we yeet while doing this
- We now have M' <= M guards watching N' <= N bushes with K' <= K ninja such that each
  guard watches at least 2 bushes
- View each guard as a line segment and each ninja as a point
    - Since the input is guaranteed to be valid, we know that we can use at most K points
      to "cover" all the segments
    - Notice that we can guarantee the locations of any of the K' ninja iff we need
      **exactly** K points to cover all the segments (otherwise we can shift ninja around)
- Using DP, we can find both the minimum number of points needed and which positions
  **must** have a point in any optimal construction
    - dp[i] = Min no. of points needed to cover segments in [1, i] and there's a point on i
            = min(dp[j] + 1 : No segment is completely contained in (j, i))
    - From calculating dp, we can build a "dependency graph" and see which positions are
      articulation points on that graph. These points are the fixed points
- Complexity: O(N^2) (this passes in 0.1s on all OJs???)
*/

#include <bits/stdc++.h>
using namespace std;

int pref[100002], diff[100002];

vector<int> events[100002], dep_graph[100002];
int latest[100002], dp[100002], cnt[100002];
bool bad[100002], visited[100002];

void dfs(int bush) {
    visited[bush] = true;
    cnt[dp[bush]]++;
    for (int i : dep_graph[bush]) if (!visited[i]) dfs(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k;
    vector<pair<int, int>> yes;
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        if (x) yes.push_back({a, b});
        else diff[a]++, diff[b + 1]--;
    }

    int active = 0;
    for (int i = 1; i <= n; i++) {
        active += diff[i];
        bad[i] = (active != 0);
        pref[i] = pref[i - 1] + (active == 0);
    }

    if (pref[n] == k) {
        for (int i = 1; i <= n; i++) if (pref[i] - pref[i - 1]) cout << i << '\n';
    } else {
        set<int> confirmed;
        vector<pair<int, int>> tmp, maybe;
        for (pair<int, int> i : yes) {
            if (pref[i.second] - pref[i.first - 1] == 1) {
                int l = i.first, r = i.second;
                while (l != r) {
                    int mid = (l + r) / 2;
                    if (pref[mid] - pref[i.first - 1]) r = mid;
                    else l = mid + 1;
                }
                confirmed.insert(l);
            } else tmp.push_back(i);
        }
        k -= confirmed.size();
        for (pair<int, int> i : tmp) {
            if (confirmed.lower_bound(i.first) == confirmed.upper_bound(i.second)) {
                events[i.second + 1].push_back(maybe.size());
                maybe.push_back(i);
            }
        }

        for (int i = 1; i <= n + 1; i++) {
            latest[i] = latest[i - 1];
            for (int j : events[i]) latest[i] = max(latest[i], maybe[j].first);
        }

        memset(dp, 0x3f, sizeof dp);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            if (bad[i]) continue;
            for (int j = latest[i]; j < i; j++) {
                if (dp[j] < dp[i]) dp[i] = dp[j], dep_graph[i].clear();
                if (dp[j] == dp[i]) dep_graph[i].push_back(j);
            }
            dp[i]++;
        }
        if (*min_element(dp + latest[n + 1], dp + n + 1) == k) {
            for (int i = latest[n + 1]; i <= n; i++) if (dp[i] == k) dfs(i);
            for (int i = 1; i <= n; i++) if (visited[i] && cnt[dp[i]] == 1) confirmed.insert(i);
        }

        if (!confirmed.size()) cout << -1;
        else for (int i : confirmed) cout << i << '\n';
    }
    return 0;
}
