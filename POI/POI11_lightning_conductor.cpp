#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int n, h[500000], dp1[500000], dp2[500000];

double slope(int j, int k) {
    double a = (k - j) / 2.0 / (h[k] - h[j]) - (h[k] - h[j]) / 2.0;
    return a * a + k;
}

void solve(int dp[]) {
    deque<int> q;
    FOR(i, 0, n) {
        // Keep the queue monotone
        if (!i || h[q.back()] < h[i]) {
            while ((q.size() > 0 &&
                    h[i] >= h[q.back()] + ceil(sqrt(i - q.back()))) ||
                   (q.size() > 1 &&
                    slope(q[q.size() - 2], q.back()) > slope(q.back(), i)))
                q.pop_back();
            q.push_back(i);
        }
        while (q.size() > 1 && slope(q[0], q[1]) < i) q.pop_front();
        dp[i] = h[q[0]] + ceil(sqrt(i - q[0]));
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, 0, n) cin >> h[i];

    solve(dp1);
    FOR(i, 0, n / 2) swap(h[i], h[n - 1 - i]);
    solve(dp2);

    FOR(i, 0, n) cout << max(dp1[i], dp2[n - 1 - i]) - h[n - 1 - i] << '\n';
    return 0;
}