#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

pair<int, int> dp[220001];
int a[220001], pref[220001];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    deque<int> dq;
    dq.push_back(0);
    FOR(i, 1, n + 1) {
        while (dq.front() < i - m) dq.pop_front();
        dp[i] = {dp[dq.front()].second + pref[i] - pref[dq.front()], dp[dq.front()].first};
        while (dq.size() && dp[dq.back()].second + pref[i] - pref[dq.back()] <= dp[i].second) dq.pop_back();
        dq.push_back(i);
    }

    cout << dp[n].first;
    return 0;
}