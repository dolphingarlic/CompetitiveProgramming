#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[2000001];
priority_queue<pair<int, pair<int, ll>>> pq;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        while (pq.size() && pq.top().first == -i) {
            pair<int, pair<int, ll>> nxt = pq.top();
            a[i] -= nxt.second.second;
            pq.push({nxt.first - nxt.second.first, nxt.second});
            pq.pop();
        }
        if (a[i]) pq.push({-2 * i, {i, a[i]}});
    }
    cout << pq.size();
    return 0;
}