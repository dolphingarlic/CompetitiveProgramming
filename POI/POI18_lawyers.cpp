#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

pair<int, int> a[1000000];
int n, k;

bool check(int itv) {
    vector<pair<int, int>> events;
    FOR(i, 0, n) {
        if (a[i].second - itv + 1 > a[i].first) {
            events.push_back({a[i].first, 1});
            events.push_back({a[i].second - itv + 1, -1});
        }
    }
    sort(events.begin(), events.end());

    int cnt = 0;
    for (auto& i : events) {
        cnt += i.second;
        if (cnt == k) return true;
    }
    return false;
}

set<int> get_ans(int itv) {
    set<int> ans;
    vector<pair<pair<int, int>, int>> events;
    FOR(i, 0, n) {
        if (a[i].second - itv + 1 > a[i].first) {
            events.push_back({{a[i].first, 1}, i + 1});
            events.push_back({{a[i].second - itv + 1, -1}, i + 1});
        }
    }
    sort(events.begin(), events.end());

    int cnt = 0;
    for (auto& i : events) {
        if (i.first.second == 1) ans.insert(i.second);
        else ans.erase(i.second);
        cnt += i.first.second;

        if (cnt == k) return ans;
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    FOR(i, 0, n) {
        cin >> a[i].first >> a[i].second;
    }

    int l = 1, r = (int)1e9;
    while (l != r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << l << '\n';
    set<int> ans = get_ans(l);
    for (int i : ans) cout << i << ' ';
    return 0;
}