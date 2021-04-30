/*
COI 2021 Autobahn
- This code is disgusting and probably wrong. Please move along
- Complexity: O(Good enough for the subtasks)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k, x;
    cin >> n >> k >> x;
    if (n <= 1000) {
        vector<int> motorists(1001), fines(1001);
        for (int i = 1; i <= n; i++) {
            int l, t, r;
            cin >> l >> t >> r;
            for (int j = l; j <= r; j++) motorists[j]++;
            for (int j = l + t; j <= r; j++) fines[j]++;
        }
        int ans = 0;
        for (int i = 1; i <= 1000; i++) {
            if (motorists[i] < k) fines[i] = 0;
            fines[i] += fines[i - 1];
            if (i >= x) ans = max(ans, fines[i] - fines[i - x]);
        }
        cout << ans;
    } else {
        vector<pair<ll, int>> events;
        for (int i = 1; i <= n; i++) {
            ll l, t, r;
            cin >> l >> t >> r;
            events.push_back({l, 2});
            events.push_back({r + 1, -2});
            if (t < r - l) {
                events.push_back({l + t, 1});
                events.push_back({r + 1, -1});
            }
        }
        sort(events.begin(), events.end());

        int curr_l = 0;
        int motorists = 0;
        ll fines = 0;
        vector<pair<pair<int, int>, ll>> segs;
        for (int i = 0; i < events.size(); i++) {
            if (!i || events[i].first != events[i - 1].first) {
                if (motorists >= k && fines)
                    segs.push_back({{curr_l, events[i].first - 1}, fines});
                curr_l = events[i].first;
            }

            if (events[i].second == 2) motorists++;
            else if (events[i].second == -2) motorists--;
            else if (events[i].second == 1) fines++;
            else fines--;
        }

        vector<ll> pref = {0};
        for (auto i : segs) {
            pref.push_back(i.second * (i.first.second - i.first.first + 1));
            pref.back() += pref[pref.size() - 2];
        }
        ll ans = 0;
        for (int i = 0, j = 0; i < segs.size(); i++) {
            while (segs[i].first.second - x >= segs[j].first.second)
                j++;
            if (segs[i].first.second - x < segs[j].first.first)
                ans = max(ans, pref[i + 1] - pref[j]);
            else
                ans = max(ans, pref[i + 1] - pref[j + 1] + segs[j].second * (segs[j].first.second - (segs[i].first.second - x)));
        }
        for (int i = segs.size() - 1, j = segs.size() - 1; ~i; i--) {
            while (segs[i].first.first + x <= segs[j].first.first)
                j--;
            if (segs[i].first.first + x > segs[j].first.second)
                ans = max(ans, pref[j + 1] - pref[i]);
            else
                ans = max(ans, pref[j] - pref[i] + segs[j].second * ((segs[i].first.first + x) - segs[j].first.first));
        }

        cout << ans;
    }
    return 0;
}
