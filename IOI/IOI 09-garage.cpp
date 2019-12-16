#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

priority_queue<int> pq;
int r[100], w[2001], curr[2001];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) {
        cin >> r[i];
        pq.push(-i);
    }

    int ans = 0;
    FOR(i, 1, m + 1) cin >> w[i];

    queue<int> q;
    FOR(i, 0, 2 * m) {
        int c;
        cin >> c;
        if (c > 0) q.push(c);
        else pq.push(-curr[-c]);

        while (pq.size() && q.size()) {
            curr[q.front()] = -pq.top();
            ans += w[q.front()] * r[-pq.top()];
            pq.pop(); q.pop();
        }
    }

    cout << ans;
    return 0;
}