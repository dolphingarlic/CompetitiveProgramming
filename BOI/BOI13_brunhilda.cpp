#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MAXN 10000001
typedef long long ll;
using namespace std;

ll dp[MAXN];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    deque<int> dq;
    FOR(i, 0, n) {
        int k;
        cin >> k;
        dq.push_back(k);
    }

    dp[0] = 0;
    FOR(i, 1, MAXN) {
        dp[i] = INT_MAX;
        for (int j = 0; j < n && i % dq.front() == 0; j++) {
            dq.push_back(dq.front());
            dq.pop_front();
        }

        dp[i] = dp[i - (i % dq.front())] + 1;
    }

    FOR(i, 0, q) {
        int x;
        cin >> x;
        if (dp[x] >= INT_MAX) cout << "oo\n";
        else cout << dp[x] << '\n';
    }
    return 0;
}