/*
IZhO 2019 Bigger Segments
- dp[i] = {Maximum no. of segments for first i, Min sum of the last segment to get that maximum}
        = max(dp[j]) + 1 where pref[i] - pref[j] >= dp[j].second
- Notice how the optimal j is nondecreasing
- This means we can simply use a monotone deque to calculate dp
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[500001], pref[500001];
pair<int, ll> dp[500001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    deque<int> dq = {0};
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
        while (dq.size() > 1 && pref[i] - pref[dq[1]] >= dp[dq[1]].second)
            dq.pop_front();
        dp[i] = {dp[dq[0]].first + 1, pref[i] - pref[dq[0]]};
        while (dq.size() && dp[dq.back()].second - dp[i].second >= pref[i] - pref[dq.back()])
            dq.pop_back();
        dq.push_back(i);
    }
    cout << dp[n].first;
    return 0;
}