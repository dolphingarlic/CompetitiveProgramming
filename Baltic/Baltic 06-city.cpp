#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll diff[20001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, t, k;
    cin >> n >> t >> k;
    FOR(i, 1, k + 1) {
        cin >> diff[i];
        diff[i - 1] -= diff[i];
    }

    priority_queue<tuple<ll, ll, ll>> pq;
    pq.push({diff[0], 1, 4});

    int dist = 1;
    ll ans = 0;
    while (n) {
        ll cost, level, capacity;
        tie(cost, level, capacity) = pq.top();
        pq.pop();

        capacity = min(n, capacity);
        ans -= cost * capacity;
        n -= capacity;

        if (level < k) pq.push({cost + diff[level], level + 1, capacity});
        if (!pq.size() || diff[0] - t * dist > get<0>(pq.top())) {
            pq.push({diff[0] - t * dist, 1, 4 * dist + 4});
            dist++;
        }
    }
    cout << ans;
    return 0;
}