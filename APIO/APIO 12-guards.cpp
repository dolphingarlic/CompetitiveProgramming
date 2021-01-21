#include <bits/stdc++.h>
using namespace std;

int pref[100001], diff[100002];

vector<int> events[100001], has_dp[100001];
int latest[100001], dp[100001], cnt[100001];

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
                k--;
            } else tmp.push_back(i);
        }
        for (pair<int, int> i : tmp) {
            if (confirmed.lower_bound(i.first) == confirmed.upper_bound(i.second)) {
                events[i.second + 1].push_back(maybe.size());
                maybe.push_back(i);
            }
        }

        for (int i = 1; i <= n; i++) {
            latest[i] = latest[i - 1];
            for (int j : events[i]) latest[i] = max(latest[i], maybe[j].first);
        }

        memset(dp, 0x3f, sizeof dp);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = latest[i]; j < i; j++) {
                if (dp[j] < dp[i]) dp[i] = dp[j], cnt[i] = 0;
                if (dp[j] == dp[i]) cnt[i]++;
            }
            has_dp[++dp[i]].push_back(i);
        }
        if (*min_element(dp + latest[n], dp + n +  1) == k) {
            // There are potential ninjas to confirm
        }

        if (!confirmed.size()) cout << -1;
        else for (int i : confirmed) cout << i << '\n';
    }
    return 0;
}
